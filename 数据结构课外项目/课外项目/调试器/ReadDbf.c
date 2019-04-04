/////////////////////////////////////////////////////////////////////////
//             使用时请注意修改第100行中的文件路径和文件名             //
//             本案例只支持打开e:\Readdbf\a.dbf文件                    //
/////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#define TRUE	1
//#define FALSE	0
#define NFIELDS 5
#define FIELDGAP 1         //字段内容显示时的间隔 

typedef unsigned char byte;
/* DBF文件头结构 */
struct dbf_head{
	char vers;              //表示当前的版本信息
	unsigned char yy,mm,dd; //表示最近的更新日期，按照YYMMDD格式。
	unsigned int no_recs;   //文件中的记录条数
	unsigned short head_len;//文件头中的字节数
	unsigned short rec_len; //一条记录中的字节长度
	char reserved[20];      //保留 
};

/* DBF字段描述结构 */
struct field_element{
	char field_name[11];        //字段名 
	char field_type;            //字段类型 
	unsigned int offset;        //保留字
	unsigned char field_length; //字段长度 
	unsigned char field_decimal;//字段的精度（小数位数） 
	char reserved1[2];          //保留字
	char dbaseiv_id;            //工作区ID
	char reserved2[10];         //保留字
	char production_index;      //如果存在一个MDX 格式的索引文件，那么这个记录项为真
};

char *dbf_fields_name[NFIELDS]={
	"a", "b","c","d","e"
};

/* 全局变量 */
struct dbf_head file_head;    //存放DBF文件头 
struct field_element *fields; //存放字段记录数组 
int *field_ShowWidth;        //字段相应的显示宽度 （取字段长度与字段名称的最大值） 

//fld_count   :字段数 
//fields      :字段数组
//fldShowWidth：字段显示宽度 
//buff        :存放记录数据 
void ShowTitle(int fld_count,struct field_element *_fields,int *fldShowWidth)
{int fldindex,loop;
 char *p;
 for (fldindex=0;fldindex<fld_count;fldindex++)
       {
        p=fields[fldindex].field_name;
		for (loop=0;loop<fldShowWidth[fldindex];loop++)    
		   if (loop<fields[fldindex].field_length)
             putchar(*(p+loop));
           else
             putchar(' ');
        for (loop=0;loop<FIELDGAP;loop++)
            putchar(' ');
       }
    printf("\n");
}
void ShowSeparate(int fld_count,struct field_element *_fields,int *fldShowWidth,char * buff)
{int fldindex,loop;
 char *p;
 if (buff[0]!='\x2a')//记录删除标志 
  {
  	for (fldindex=0;fldindex<fld_count;fldindex++)
       {
       	p=buff+fields[fldindex].offset;//字段数据的首地址
		for (loop=0;loop<fldShowWidth[fldindex];loop++)    
		   if (loop<fields[fldindex].field_length)
             putchar(*(p+loop));
           else
             putchar(' ');
        for (loop=0;loop<FIELDGAP;loop++)
            putchar(' ');
       }
    printf("\n");
 }
}

/* 主函数代码 */
int main()
{
	register int i,j;
	FILE *fp_dat;
	char *buffer;
	char *allspace;
	int fields_count;
	unsigned int counts;

	/* 打开dbf文件,注意此处 */
	if((fp_dat=fopen("D:\\a.dbf","rb"))==NULL){
		fprintf(stderr,"Cannot open dbf file to read!\n");
		exit(1);
	}

	/* 读取表头纪录 */
	fseek(fp_dat,0L,SEEK_SET);
	fread((void*)&file_head,sizeof(struct dbf_head),1,fp_dat);
	/*
	revert_unsigned_int(&file_head.no_recs);
	revert_unsigned_short(&file_head.head_len);
	revert_unsigned_short(&file_head.rec_len);
	*/
	/* 计算字段数 */
//	fields_count=(file_head.head_len-sizeof(struct dbf_head)-1-263)/sizeof(struct field_element);
	fields_count=(file_head.head_len-sizeof(struct dbf_head)-1)/sizeof(struct field_element);
	
	/* 开辟存储字段子记录的空间 */
	if((fields=(struct field_element*)malloc(sizeof(struct field_element)*fields_count))==NULL){
		fprintf(stderr,"Cannot allocate memory for fields array !\n");
		fclose(fp_dat);
		exit(2);
	}
	
	/* 开辟存储一条数据记录的空间 */
	if((buffer=(char*)malloc(sizeof(char)*file_head.rec_len))==NULL){
		fprintf(stderr,"Cannot allocate memory for record buffer!\n");
		fclose(fp_dat);
		exit(3);
	}
	
	/* 开辟一个全为空格的纪录，以便后面做比较 */
	if((allspace=(char*)malloc(sizeof(char)*file_head.rec_len))==NULL){
		fprintf(stderr,"Cannot allocate memory for all_space record buffer!\n");
		fclose(fp_dat);
		exit(4);
	}
	else{
		memset((void*)allspace,'\x20',file_head.rec_len-1);
		allspace[file_head.rec_len]='\0';
	}
	/* 开辟显示宽度数组 */
	field_ShowWidth=(int*)malloc(sizeof(int)*fields_count);
	if(field_ShowWidth==NULL){
		fprintf(stderr,"Cannot allocate memory for array field_ShowWidth.\n");
		exit(-1);
	}
	
	/* 读取所有的字段子记录*/
	fread((void*)fields,sizeof(struct field_element),fields_count,fp_dat);
	/* 计算各个字段的字节偏移量，第一字节为删除标记 */	
   	fields[0].offset=1;
	for(i=1;i<fields_count;i++)
		 fields[i].offset=fields[i-1].offset+(unsigned short)fields[i-1].field_length;//用于分离字段数据 
	for(i=0;i<fields_count;i++)
		field_ShowWidth[i]=(strlen(fields[i].field_name)>fields[i].field_length?strlen(fields[i].field_name):fields[i].field_length);//用于字段显示数据宽度的控制 

   ShowTitle(fields_count,fields,field_ShowWidth);

	/* 定位文件指针到数据记录的开始位置 */
	fseek(fp_dat,file_head.head_len,SEEK_SET);
	
	/* 读取每条记录的字段数据 */
	for(counts=0;counts<file_head.no_recs;counts++)
	{
		fread((void*)buffer,(int)file_head.rec_len,1,fp_dat);
		ShowSeparate(fields_count,fields,field_ShowWidth,buffer);
	}
	
	fclose(fp_dat);
	
	/* 释放开辟的空间 */
	free(buffer);
	free(field_ShowWidth);
	free(allspace);
}

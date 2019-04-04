/////////////////////////////////////////////////////////////////////////
//             ʹ��ʱ��ע���޸ĵ�100���е��ļ�·�����ļ���             //
//             ������ֻ֧�ִ�e:\Readdbf\a.dbf�ļ�                    //
/////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#define TRUE	1
//#define FALSE	0
#define NFIELDS 5
#define FIELDGAP 1         //�ֶ�������ʾʱ�ļ�� 

typedef unsigned char byte;
/* DBF�ļ�ͷ�ṹ */
struct dbf_head{
	char vers;              //��ʾ��ǰ�İ汾��Ϣ
	unsigned char yy,mm,dd; //��ʾ����ĸ������ڣ�����YYMMDD��ʽ��
	unsigned int no_recs;   //�ļ��еļ�¼����
	unsigned short head_len;//�ļ�ͷ�е��ֽ���
	unsigned short rec_len; //һ����¼�е��ֽڳ���
	char reserved[20];      //���� 
};

/* DBF�ֶ������ṹ */
struct field_element{
	char field_name[11];        //�ֶ��� 
	char field_type;            //�ֶ����� 
	unsigned int offset;        //������
	unsigned char field_length; //�ֶγ��� 
	unsigned char field_decimal;//�ֶεľ��ȣ�С��λ���� 
	char reserved1[2];          //������
	char dbaseiv_id;            //������ID
	char reserved2[10];         //������
	char production_index;      //�������һ��MDX ��ʽ�������ļ�����ô�����¼��Ϊ��
};

char *dbf_fields_name[NFIELDS]={
	"a", "b","c","d","e"
};

/* ȫ�ֱ��� */
struct dbf_head file_head;    //���DBF�ļ�ͷ 
struct field_element *fields; //����ֶμ�¼���� 
int *field_ShowWidth;        //�ֶ���Ӧ����ʾ��� ��ȡ�ֶγ������ֶ����Ƶ����ֵ�� 

//fld_count   :�ֶ��� 
//fields      :�ֶ�����
//fldShowWidth���ֶ���ʾ��� 
//buff        :��ż�¼���� 
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
 if (buff[0]!='\x2a')//��¼ɾ����־ 
  {
  	for (fldindex=0;fldindex<fld_count;fldindex++)
       {
       	p=buff+fields[fldindex].offset;//�ֶ����ݵ��׵�ַ
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

/* ���������� */
int main()
{
	register int i,j;
	FILE *fp_dat;
	char *buffer;
	char *allspace;
	int fields_count;
	unsigned int counts;

	/* ��dbf�ļ�,ע��˴� */
	if((fp_dat=fopen("D:\\a.dbf","rb"))==NULL){
		fprintf(stderr,"Cannot open dbf file to read!\n");
		exit(1);
	}

	/* ��ȡ��ͷ��¼ */
	fseek(fp_dat,0L,SEEK_SET);
	fread((void*)&file_head,sizeof(struct dbf_head),1,fp_dat);
	/*
	revert_unsigned_int(&file_head.no_recs);
	revert_unsigned_short(&file_head.head_len);
	revert_unsigned_short(&file_head.rec_len);
	*/
	/* �����ֶ��� */
//	fields_count=(file_head.head_len-sizeof(struct dbf_head)-1-263)/sizeof(struct field_element);
	fields_count=(file_head.head_len-sizeof(struct dbf_head)-1)/sizeof(struct field_element);
	
	/* ���ٴ洢�ֶ��Ӽ�¼�Ŀռ� */
	if((fields=(struct field_element*)malloc(sizeof(struct field_element)*fields_count))==NULL){
		fprintf(stderr,"Cannot allocate memory for fields array !\n");
		fclose(fp_dat);
		exit(2);
	}
	
	/* ���ٴ洢һ�����ݼ�¼�Ŀռ� */
	if((buffer=(char*)malloc(sizeof(char)*file_head.rec_len))==NULL){
		fprintf(stderr,"Cannot allocate memory for record buffer!\n");
		fclose(fp_dat);
		exit(3);
	}
	
	/* ����һ��ȫΪ�ո�ļ�¼���Ա�������Ƚ� */
	if((allspace=(char*)malloc(sizeof(char)*file_head.rec_len))==NULL){
		fprintf(stderr,"Cannot allocate memory for all_space record buffer!\n");
		fclose(fp_dat);
		exit(4);
	}
	else{
		memset((void*)allspace,'\x20',file_head.rec_len-1);
		allspace[file_head.rec_len]='\0';
	}
	/* ������ʾ������� */
	field_ShowWidth=(int*)malloc(sizeof(int)*fields_count);
	if(field_ShowWidth==NULL){
		fprintf(stderr,"Cannot allocate memory for array field_ShowWidth.\n");
		exit(-1);
	}
	
	/* ��ȡ���е��ֶ��Ӽ�¼*/
	fread((void*)fields,sizeof(struct field_element),fields_count,fp_dat);
	/* ��������ֶε��ֽ�ƫ��������һ�ֽ�Ϊɾ����� */	
   	fields[0].offset=1;
	for(i=1;i<fields_count;i++)
		 fields[i].offset=fields[i-1].offset+(unsigned short)fields[i-1].field_length;//���ڷ����ֶ����� 
	for(i=0;i<fields_count;i++)
		field_ShowWidth[i]=(strlen(fields[i].field_name)>fields[i].field_length?strlen(fields[i].field_name):fields[i].field_length);//�����ֶ���ʾ���ݿ�ȵĿ��� 

   ShowTitle(fields_count,fields,field_ShowWidth);

	/* ��λ�ļ�ָ�뵽���ݼ�¼�Ŀ�ʼλ�� */
	fseek(fp_dat,file_head.head_len,SEEK_SET);
	
	/* ��ȡÿ����¼���ֶ����� */
	for(counts=0;counts<file_head.no_recs;counts++)
	{
		fread((void*)buffer,(int)file_head.rec_len,1,fp_dat);
		ShowSeparate(fields_count,fields,field_ShowWidth,buffer);
	}
	
	fclose(fp_dat);
	
	/* �ͷſ��ٵĿռ� */
	free(buffer);
	free(field_ShowWidth);
	free(allspace);
}

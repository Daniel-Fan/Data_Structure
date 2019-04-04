#include<stdio.h>
#include<conio.c>
#include<windows.h>
#define NumberOfTotalSign 9
#define NumberOfEachLineSign 3
#define UpLeftSigh 0xDA
#define UpRightSign 0xBF
#define DownLeftSign 0xC0
#define DownRightSign 0xD9
#define BlankSign 0x20
#define RowSign 0xB3
#define lineSign 0xC4
int Sign[NumberOfTotalSign]={UpLeftSigh,lineSign,UpRightSign,RowSign,BlankSign,RowSign,DownLeftSign,RowSign,DownRightSign};
void ShowALineOfBox(COORD upleft,int breadth,int s[NumberOfEachLineSign],int Color1,int Color2)
{
	int x;
	gotoxy(upleft.X,upleft.Y);
	textattr(Color1);
	printf("%c",Sign[0]);
	for(x=1;x<=breadth;x++)
	{
		textattr(Color2);
		printf("%c",Sign[1]);
	}
	textattr(Color1);
	printf("%c",Sign[2]);
}
void ShowBox(COORD upleft,COORD downright,int s[NumberOfTotalSign],int Color1,int Color2)
{
	int y;
	ShowALineOfBox(upleft,downright.X-upleft.X+1,&s[0],Color1,Color2);
	for(y=1;y<=downright.Y-upleft.Y-1;y++)
	{
		ShowALineOfBox({upleft.X,upleft.Y+y},downright.X-upleft.X+1,&s[NumberOfEachLineSign],Color1,Color2);
	}
	ShowALineOfBox({upleft.X,downright.Y},downright.X-upleft.X+1,&s[2*NumberOfEachLineSign],Color1,Color2);
}

int main()
{
	ShowBox({1,1},{80,25},Sign,BLUE,LIGHTGRAY);
}

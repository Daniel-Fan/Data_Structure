#include"stdio.h"
#include<windows.h>
#include<conio.c> 
#define NumberOfTotalSign 9
#define NumberOfEachLineSign 3
#define UpLeftSigh 0xDA
#define UpRightSign 0xBF
#define DownLeftSign 0xC0
#define DownRightSign 0xD9
#define BlankSign 0x20
#define RowSign 0xB3
#define LineSign 0xC4
#define UpLeftX 0
#define UpLeftY 1
#define DownRightX 80
#define DownRightY 25
#define Color1 BLUE
#define Color2 LIGHTGRAY
int Sign[NumberOfTotalSign]={UpLeftSigh,LineSign,UpRightSign,RowSign,BlankSign,RowSign,DownLeftSign,LineSign,DownRightSign};
void ShowALineOfBox(int upleftX,int upleftY,int breadth,int s[NumberOfEachLineSign],int color1,int color2)
{
	int x,*p;
	p=s;
	gotoxy(upleftX,upleftY);
	textbackground(color1);
	printf("%c",*p);
	for(x=1;x<breadth-1;x++)
	{
		textbackground(color2);
		printf("%c",*(p+1));
	}
	textbackground(color1);
	printf("%c",*(p+2));
	textbackground(BLACK);
}
void ShowBox(int upleftX,int upleftY,int downrightX,int downrightY,int s[NumberOfTotalSign],int color1,int color2)
{
	int y;
	ShowALineOfBox(upleftX,upleftY,downrightX-upleftX,&s[0],color1,color1);
	for(y=1;y<=downrightY-upleftY-1;y++)
	{
		ShowALineOfBox(upleftX,upleftY+y,downrightX-upleftX,&s[NumberOfEachLineSign],color1,color2);
	}
	ShowALineOfBox(upleftX,downrightY,downrightX-upleftX,&s[2*NumberOfEachLineSign],color1,color1);
}

int main()
{
	clrscr();
	ShowBox(UpLeftX,UpLeftY,DownRightX,DownRightY,Sign,Color1,Color2);
}

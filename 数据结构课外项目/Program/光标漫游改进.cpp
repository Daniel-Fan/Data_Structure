#include<stdio.h>
#include "conio.c"
int x,y;
#define EscKey 27
#define EnterKey 13
#define UpCursor 38
#define RightCursor 39
#define DownCursor 40
#define LeftCursor 37
void Esckey()
{
	exit(0);
} 
void Enterkey()
{
	y=y+1;
}
void Upcursor()
{
	y=(y+24)%25;
} 
void Rightcursor()
{
	x=(x+1)%80;
}
void Downcursor()
{
	y=(y+1)%25;
}
void Leftcursor()
{
	x=(x+79)%80;
}
int main()
{
	int z;
	KeyValueStru CurrentKey;
	int menuKey[]={EscKey,EnterKey,UpCursor,RightCursor,DownCursor,LeftCursor};
	void (*menufun[])()={Esckey,Enterkey,Upcursor,Rightcursor,Downcursor,Leftcursor};
	do
	{
		CurrentKey=kbhit();
		for(z=0;z<6;z++)
		{
            if(menuKey[z]==CurrentKey.VKey)
		    {
			   menufun[z]();
			   break;
            }
		}
	}
	while(1);
	return 0;
}

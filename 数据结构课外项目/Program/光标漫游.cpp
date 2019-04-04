#include<stdio.h>
#include "conio.c"
#include<windows.h>
#include<string.h>
#define EscKey 27
#define EnterKey 13
#define Upcursor 38
#define Rightcursor 39
#define Downcursor 40
#define Leftcursor 37
int main()
{
	
	KeyValueStru CurrentKey;
	int x,y;
	x=0;y=0;
	do
	{
		CurrentKey=kbhit();
		if(CurrentKey.AscChar==0)
		{
			switch(CurrentKey.VKey)
			{
				case Downcursor:y=(y+1)%25;break;
				case Rightcursor:x=(x+1)%80;break;
				case Upcursor:y=(y+24)%25;break;
				case Leftcursor:x=(x+79)%80;break;
			}
			gotoxy(x,y);
		}
	}
	while(CurrentKey.VKey!=27);
	return 0;
}

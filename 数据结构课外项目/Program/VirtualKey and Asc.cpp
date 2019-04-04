#include<stdio.h>
#include "conio.c"
#include<windows.h>
#include<string.h>
int main()
{
	int i;
	KeyValueStru CurrentKey;
	for(i=0;i<10;i++)
	{
		CurrentKey=kbhit();
    printf("AsciiChar=%2d VirtualKey=%2d\n",CurrentKey.AscChar,CurrentKey.VKey);
	}
	
	return 0;
}

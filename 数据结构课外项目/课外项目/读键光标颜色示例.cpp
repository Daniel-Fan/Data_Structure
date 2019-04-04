#include<stdio.h>
#include "conio.c"
#include<windows.h>
#include<string.h>
int main()
{
    KeyValueStru CurrentKey;
    CurrentKey=kbhit();
    clrscr();
    CurrentKey=kbhit();
    printf("AsciiChar=%2x VirtualKey=%2x",CurrentKey.AscChar,CurrentKey.VKey);
    CurrentKey=kbhit();
    textattr(0x40);
    gotoxy(2,0);
	printf("djkdsjfkjsdkfj\nasdfsaasafsdfsaf\ndfssssssssssssssssssss\nsdfffffffffffffffffff\nsdffffffffffff\n");
	getchar();
}

#include "conio.c"

int main()
{
int loopi,loopj;
SetConsoleTitle("��ʾ������ASCII��"); // ���ô��ڱ���
clrscr();
printf("  ");
for (loopi=0;loopi<=15;loopi++)
  printf("%2X",loopi);
printf("\n");
for (loopi=0;loopi<=15;loopi++)
  {printf("%2X",loopi);
   for(loopj=0;loopj<=15;loopj++)
    if ((loopi*16)+loopj<32)
      printf("%2c",'.');
    else printf("%2c",(loopi*16)+loopj);
   printf("\n");
  }
getch();	
}
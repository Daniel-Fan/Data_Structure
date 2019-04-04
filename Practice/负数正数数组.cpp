#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 10
int a[N];
int *q,*p;
int temp;
int sequence()
{
	q=a;
    p=&a[N-1];
	do
	{
		while(*q<0&&q<p)
		{
			q++;
		}
		while(*p>=0&&q<p)
		{
			p--;
		}
		while(*q>=0&&*p<0)
		{
			temp=*q;
		    *q=*p;
		    *p=temp;
		}
	}while(q<p);
}

int main()
{
	srand(time(0));
	int i;
	for(i=0;i<N;i++)
	{
		a[i]=rand()%51-25;
		printf("%d ",a[i]);
	}
	printf("\n");
	sequence();
	for(i=0;i<N;i++)
	{
		printf("%d ",a[i]);
	}
	return 0;
}

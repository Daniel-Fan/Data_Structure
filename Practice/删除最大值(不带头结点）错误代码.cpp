#include<stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include<time.h>
#define N 20
#define LEN sizeof(struct LinkList)
typedef struct LinkList
	{
		int number;
		struct LinkList *next;
	}LinkList,*Linklist;

struct LinkList *creat()
{
    Linklist head,p1,p2;
	srand(time(NULL));  
	int i;
    for(i=0;i<N;i++)
    {
    	p1=(struct LinkList*)malloc(LEN);
    	p1->number=rand()%51;
    	if(i==0)
        head=p1;
	    else 
	    p2->next=p1;
	    p2=p1;
    }
	p1->next=NULL;
    return (head); 
}
void Print(Linklist head)
{
	Linklist p;
	p=head;
	if(head!=NULL)
	do
	{
		printf("%d ",p->number);
		p=p->next;
	}while(p!=NULL);
}

void Maxdelete(Linklist head)
{
	int i;
	Linklist p,temp,max;
	max=head;
	p=head;
	do
	{
		if(max->number<p->next->number)
		{
			max=p->next;
			temp=p;
		}
		p=p->next;
	}while(p->next!=NULL);
	if(max==head)
	{
		head=head->next;
	}
	else
	{
		temp->next=max->next;
	}
	free(max);
}

int main()
{
	struct LinkList *head;
	head=creat();
	Print(head);
	printf("\n");
	Maxdelete(head);
	Print(head);
}

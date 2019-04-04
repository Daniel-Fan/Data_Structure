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
    struct LinkList *head,*p1;
	srand(time(NULL));  
	int i;
	head=(struct LinkList*)malloc(LEN);
	head->next=NULL;
    for(i=0;i<N;i++)
    {
    	p1=(struct LinkList*)malloc(LEN);
    	p1->number=rand()%51;
    	p1->next=head->next;
    	head->next=p1;
    }	
    return (head); 
}

void Print(Linklist head)
{
	Linklist p;
	p=head->next;
	if(head->next!=NULL)
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
	max=head->next;
	p=head;
	temp=p;
	do
	{
		if(max->number<p->next->number)
		{
			max=p->next;
			temp=p;
		}
		p=p->next;
	}while(p->next!=NULL);
	temp->next=max->next;
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

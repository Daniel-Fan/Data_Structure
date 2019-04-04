#include<stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include<time.h>
#define N 20
#define LEN sizeof(struct LinkList)
struct LinkList
	{
		int number;
		struct LinkList *next;
	};

struct LinkList *creat()
{
    struct LinkList *head,*p1;
	srand(time(NULL));  
	int i;
	head=NULL;
    for(i=0;i<N;i++)
    {
    	p1=(struct LinkList*)malloc(LEN);
    	p1->number=rand()%51;
    	p1->next=head;
    	head=p1;
    }	
    return (head); 
}
void Print(struct LinkList *head)
{
	struct LinkList *p;
	p=head;
	if(head!=NULL)
	do
	{
		printf("%d ",p->number);
		p=p->next;
	}while(p!=NULL);
}

struct LinkList *adverse(struct LinkList *head)      
{
	struct LinkList *p3,*p2,*p1,*temp;
	p3=NULL;     
    p2=NULL;              
    p1=head;      
    while(p1!=NULL)      
    {      
               
         temp=p1->next;
		 if(temp==NULL)      
         {      
              p3=p1;      
         }      
         
		 p1->next=p2;      
         p2=p1;      
         p1=temp;                     
    }      
    return(p3);                  
}

int main()
{
	struct LinkList *head;
    head=creat();
    Print(head);
    printf("\n");
    head=adverse(head);
	Print(head);  
}

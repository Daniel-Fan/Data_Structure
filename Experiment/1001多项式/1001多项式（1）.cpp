#include <iostream>
#include <list>
#include <numeric>
#include <algorithm>
using namespace std;

typedef struct{
	int coefficient;
	int index;
}Polynomial;

typedef list<Polynomial> INTLIST;

int compare(int a,int b)
{
	int answer;
	if(a<b)
	{
		answer=-1;
	}
	else if(a>b)
	{
		answer=1;
	}
	else
	{
		answer=0;
	}
	return answer;
}

void addelements(INTLIST &L1,INTLIST &L2)
{
	Polynomial Temp;
	int a,b;
    int i;
    scanf("%d",&a);
    for(i=0;i<a;i++)
    {
    	scanf("%d%d",&Temp.coefficient,&Temp.index);
    	L1.push_back(Temp);
    }
    scanf("%d",&b);
    for(i=0;i<b;i++)
    {
    	scanf("%d%d",&Temp.coefficient,&Temp.index);
    	L2.push_back(Temp);
    }
}

void calculation(INTLIST &L1,INTLIST &L2)
{
	INTLIST::iterator iter1;
	INTLIST::iterator iter2;
	INTLIST::iterator iter3;
	int sum;
	iter1=L1.begin();
	iter2=L2.begin();
	while(iter1!=L1.end()&&iter2!=L2.end())
	{
		int x,y;
		x=iter1->index;
		y=iter2->index;
		switch(compare(x,y))
		{
			case -1: iter1++;break;
			case  1: L1.insert(iter1--,1,*iter2);iter2++;break;
			case  0: sum=iter1->coefficient+iter2->coefficient;
			        if(sum!=0)
			        {
        				iter1->coefficient=sum;
        			}
        			iter1++;
					iter2++;
        			break;
		}
	}
	while(iter2!=L2.end())
	{
        L1.push_back(*iter2++);
	}
}
void Print(INTLIST &L3)
{
	INTLIST::iterator iter3;
    for(iter3 = L3.begin(); iter3 != L3.end(); iter3++)
        cout << iter3->coefficient << " " << iter3->index << endl;
}
int main()
{
	INTLIST L1;
    INTLIST L2;
    addelements(L1,L2);
    calculation(L1,L2);
	printf("\n");
    Print(L1);
}
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

int main()
{
	INTLIST L1;
    INTLIST L2;
    INTLIST L3;
    //////addelements///////
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
    //////calculation/////
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
	///////printf///
	printf("\n");
	 INTLIST::iterator iter4;
    for(iter4 = L1.begin(); iter4 != L1.end(); iter4++)
        cout << iter4->coefficient << " " << iter4->index << endl;
}

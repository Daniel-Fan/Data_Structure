#include<stdio.h>
#include<string.h> 
#include <iostream>
#include <assert.h>
#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <string>
using namespace std;

int In(char Test, char* TestOp);
char LOPSET[2] = { '[' , '(' };
char Expression[20];

char *EvaluateExpression(char* MyExpression)
{
	static char Back[4];
	typedef stack<char> StackChar;
	StackChar OPTR;
	OPTR.push('#');
	char *c,Dr[2],theta;
	c=MyExpression;
	while(*c != '#' || OPTR.top() != '#')
	{
		Dr[0] = *c;
        Dr[1] = '\0';
		if (In(Dr[0], LOPSET))
		{
		   OPTR.push(Dr[0]);
		   c++;
	    }
	    else if(!In(Dr[0], LOPSET))
	    {
		   theta=OPTR.top();
		   OPTR.pop();
		   if(theta=='[')
		   {
			   if(Dr[0]==']'){
				   c++;
			   }
			   else{
				   strcpy(Back,"no");
			       return Back;
			   }
		   }
		   else if(theta=='('){
			    if(Dr[0]==')'){
			       c++;
			    }
			    else{
				   strcpy(Back,"no");
				   return Back;
			    }
		    }
        }
    	else
	    {
		    strcpy(Back,"no");
		    return Back;
	    }
	}
	strcpy(Back,"yes");
	return Back;
} 
 
int In(char Test, char* TestOp) {
	bool Find = false;
	for (int i = 0; i< 2; i++) {
		if (Test == TestOp[i]) Find = true;
	}
	return Find;
}

int main()
{
	int n;
	char *result;
	while(scanf("%s", Expression)!=EOF)
	{
		n=strlen(Expression);
		Expression[n]='#';
		result=EvaluateExpression(Expression);
		printf("%s\n", result);
	};
	return 0;
}

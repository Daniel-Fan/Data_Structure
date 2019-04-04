#include <iostream>
#include <assert.h>
#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <string>
using namespace std;

#define OPSETSIZE 7
#define Length 20
char Expression[Length];

unsigned char Prior[7][7] = { 
	'>','>','<','<','<','>','>',
	'>','>','<','<','<','>','>',
	'>','>','>','>','<','>','>',
	'>','>','>','>','<','>','>',
	'<','<','<','<','<','=',' ',
	'>','>','>','>',' ','>','>',
	'<','<','<','<','<',' ','='
};

float Operate(float a, unsigned char theta, float b);
char OPSET[OPSETSIZE] = { '+' , '-' , '*' , '/' ,'(' , ')' , '#' };
int In(char Test, char* TestOp);
char precede(char Aop, char Bop);

float EvaluateExpression(char* MyExpression)
{  
	typedef stack<char> StackChar;
	typedef stack<float> StackFloat;
	StackChar  OPTR;  
	StackFloat OPND;   

	char TempData[20];
	float Data, a, b;
	char theta, *c, x, Dr[2];

	OPTR.push('#');
	c = MyExpression;
	strcpy(TempData, "\0");
	while (*c != '#' || OPTR.top() != '#') {
		if (!In(*c, OPSET)) {
			Dr[0] = *c;
			Dr[1] = '\0';
			strcat(TempData, Dr);
			c++;
			if (In(*c, OPSET)) {
				Data = (float)atof(TempData);
				OPND.push(Data);
				strcpy(TempData, "\0");
			}
		}
		else {  
			switch (precede(OPTR.top(), *c)) {
			case '<':
				OPTR.push(*c);
				c++;
				break;
			case '=':   
				OPTR.pop();
				c++;
				break;
			case '>':   
				theta = OPTR.top();
				OPTR.pop();
				b = OPND.top();
				OPND.pop();
				a = OPND.top();
				OPND.pop();
				OPND.push(Operate(a, theta, b));
				break;
			}
		}
	} 
	return OPND.top();
}

float Operate(float a, unsigned char theta, float b) {
	switch (theta) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a*b;
	case '/': return a / b;
	default: return 0;
	}
}

int In(char Test, char* TestOp) {
	bool Find = false;
	for (int i = 0; i< OPSETSIZE; i++) {
		if (Test == TestOp[i]) Find = true;
	}
	return Find;
}


int ReturnOpOrd(char op, char* TestOp) {
	int i;
	for (i = 0; i< OPSETSIZE; i++) {
		if (op == TestOp[i]) return i;
	}
	return 0;
}

char precede(char Aop, char Bop) {
	return Prior[ReturnOpOrd(Aop, OPSET)][ReturnOpOrd(Bop, OPSET)];
}

int main()
{
	scanf("%s", Expression);
	printf("%.2f", EvaluateExpression(Expression));
}

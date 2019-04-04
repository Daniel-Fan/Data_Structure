#include<iostream>
#include<string>
#include<vector>
using namespace std;
void get_nextval(string &T, vector<int> &next) {  // 算法4.8
										 // 求模式串T的next函数修正值并存入数组nextval。
	int i = 0;
	int j = -1;
	next[0] = -1;
	while (i<T.length()-1) 
	{
		if (j==-1||T[i] == T[j]) 
		{
			++i;  ++j;
			if (T[i] != T[j])
			{
				next[i] = j;
			}
			else 
			{	
				next[i] = next[j]; 
			}
		}
		else
		{
			j = next[j];
		}
	}
} // get_nextval

int Index_KMP(string &S, string &T, int pos) 
{  // 算法4.6
  // 利用模式串T的next函数求T在主串S中第pos个字符之后的位置的
  // KMP算法。其中，T非空，1≤pos≤StrLength(S)。
  vector <int> next(T.length());
  int i = pos;
  int j = 0;
  get_nextval(T,next);
  while (i <(int)S.length() && j <(int)T.length()) 
  {
    if (j==-1||S[i] == T[j]) 
	{  // 继续比较后继字符
      ++i; 
	  ++j;
	}
	else 
	{ 
		j = next[j]; 
	} // 模式串向右移动
  }
  if (j>=(int)T.length()) return  i-(int)T.length();   // 匹配成功
  else return 0;
} // Index_KMP

int main()
{
	string S,T;
	cin >> S;
	int n,i;
	cin >> n;
	for(i=0;i<n;i++)
	{
		cin >> T;
		cout << (Index_KMP(S, T, 0)?"yes":"no")  << endl;
	}
	return 0;
}
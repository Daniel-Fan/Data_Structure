#include<iostream>
#include<string>
#include<vector>
using namespace std;
void get_nextval(string &T, vector<int> &next) {  // �㷨4.8
										 // ��ģʽ��T��next��������ֵ����������nextval��
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
{  // �㷨4.6
  // ����ģʽ��T��next������T������S�е�pos���ַ�֮���λ�õ�
  // KMP�㷨�����У�T�ǿգ�1��pos��StrLength(S)��
  vector <int> next(T.length());
  int i = pos;
  int j = 0;
  get_nextval(T,next);
  while (i <(int)S.length() && j <(int)T.length()) 
  {
    if (j==-1||S[i] == T[j]) 
	{  // �����ȽϺ���ַ�
      ++i; 
	  ++j;
	}
	else 
	{ 
		j = next[j]; 
	} // ģʽ�������ƶ�
  }
  if (j>=(int)T.length()) return  i-(int)T.length();   // ƥ��ɹ�
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
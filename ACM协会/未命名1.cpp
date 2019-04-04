#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
vector <int> v;
bool cmp(int a,int b){
	return a>b;
}
int a[10];


vector<int>::iterator it;
int main(void){
	
	
/*	for(int i=0;i<v.size();i++){
		cout<<v[i]<<" ";
	}*/
	
	/*printf("%d %d\n",a,b);
	
	swap(a,b);
	printf("%d %d\n",a,b);*/
	//printf("%d\n",max(2,3));
	
/*	a[0]=1; a[1]=2; a[2]=3;
	do{
		cout << a[0] << " " << a[1] << " " << a[2] << endl;
	}while (next_permutation(a, a+3));*/
	
	v.push_back(2);
	v.push_back(3);
	v.push_back(1);
	
	//sort(v.begin(),v.end(),cmp);
	
	it=v.begin();
//	printf("%d\n",*it);
	v.erase(it+2);
	for(int i=0;i<v.size();i++){
		
		printf("%d ",v[i]);
	}
	return 0;
}

/* 

2 3 1 


1 2 3 4 5

1 2 3 5 4


*/
#include<iostream>
#include<cstdio>
using namespace std;
int set[1001];

int find1(int i){
	if(set[i]!=i){
		set[i]=find1(set[i]);
	}
	return set[i];
}
void merge(int a,int b){
	if(a>b)
	set[a]=b;
	else
	set[b]=a;
	
}

int main(){
	int T,N,M,A,B,r1,r2;
	cin>>T;
	while(T--){
		cin>>N>>M;
		int ans=N;
		for(int i=1;i<=N;i++){
			set[i]=i;
		}
		for(int i=0;i<M;i++){
			cin>>A>>B;
			r1=find1(A);
			r2=find1(B);
			if(r1!=r2){
				merge(r1,r2);
				ans--;
			}
		}
		cout<<ans<<endl;
	}
}
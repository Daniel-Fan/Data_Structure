#include<iostream>
#include<string>
#include<set>
#include<cstdio>
using namespace std;
int n,m;
set<int>a;
set<int>::iterator it;
int main(void){
	while(scanf("%d%d",&n,&m)!=EOF){
		a.clear();
		for(int i=0;i<n;i++){
			int x;
			scanf("%d",&x);
			a.insert(x);
		}
		for(int i=0;i<m;i++){
			int x;
			scanf("%d",&x);
			it=a.find(x);
			if(it!=a.end()){
				a.erase(it);
			}
		}
		if(a.size()>0){
			for(it=a.begin();it!=a.end();it++){
				printf("%d ",*it);
			}
			printf("\n");
		}
		else{
			printf("NULL\n");
		}
	}
	
	return 0;
}
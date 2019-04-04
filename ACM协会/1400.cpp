#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<cstdio>
using namespace std;
vector<int>v;
int n,q;
vector<int>::iterator it;
int main(void){
	while(scanf("%d",&n)!=EOF){
		v.clear();
		for(int i=0;i<n;i++){
			int x; 
			scanf("%d",&x);
			v.push_back(x);
		}
		scanf("%d",&q);
		while(q--){
			int k;
			scanf("%d",&k);
			if(k>=1&&k<=v.size()){
				printf("%d\n",v[k-1]);
				it=v.begin();
				v.erase(it+k-1);
			}
			else printf("-1\n");
		}
	}
	
	return 0;
}
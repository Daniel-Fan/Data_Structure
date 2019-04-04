#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<algorithm>
#include<stdio.h>
using namespace std;
struct node{
	int x,y,z;
}NODE[100000];
bool cmp(node a,node b)
{
	if(a.x==b.x&&a.y==b.y) return a.z<b.z;
	if(a.x==b.x) return a.y<b.y;
	return a.x<b.x;
}
int main(){
	int T,n;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d%d%d",&NODE[i].x,&NODE[i].y,&NODE[i].z);
		}
		sort(NODE,NODE+n,cmp);
		printf("%d\n",n);
		for(int i=0;i<n;i++){
			printf("%d %d %d\n",NODE[i].x,NODE[i].y,NODE[i].z);
		}
	}
}
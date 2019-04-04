#include<iostream>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
bool cmp(const pair<string,int> &x,const pair<string,int> &y)
{
	return x.second<y.second;
}
int main(){
	int n;
	map<string,int> mp;
	
	string s;
	while(scanf("%d",&n)!=EOF&&n!=0){
		mp.clear();
		for(int i=0;i<n;i++){
		  cin>>s;
		  mp[s]++;
		}
	    cout<<max_element(mp.begin(),mp.end(),cmp)->first<<endl;
	}
}

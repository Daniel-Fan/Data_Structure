#include<iostream>
#include<vector>
#include<set>
#include<functional>
using namespace std;

int main()
{
	int a,b,x;
	while(cin>>a>>b){
		set<int> st;
	    st.clear();
	    for(int i=0;i<(a+b);i++){
    		cin>>x;
    		st.insert(x);
    	}
    	set<int>::iterator it; 
    	bool f=true;
	    for(it=st.begin(); it!=st.end(); it++){
	    	if(f)f=false;
	    	else cout<<' ';
		cout<<*it;
	    }
	    cout<<endl;

	}
}

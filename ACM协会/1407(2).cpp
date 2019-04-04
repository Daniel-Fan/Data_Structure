#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct point
{
	int x;
	int y;
	int z;
};
bool operator<(point a, point b)
{
return (a.x < b.x || (a.x == b.x&&a.y < b.y)) || (a.x == b.x&&a.y == b.y&&a.z < b.z);
}
int main()
{
    ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
    	vector<point>v(n);
		for (int i= 0; i < n; i++)
		{
			
			cin>>v[i].x >> v[i].y >> v[i].z;
			
		}
		cout << n << endl;
		sort(v.begin(),v.end());
		for (auto & el:v )
		{
			cout << el.x <<' '<<el.y<< ' ' << el.z<<endl;
		}
	}
	return 0;
}
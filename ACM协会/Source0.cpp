#include<stdio.h> 
#include<algorithm> 
#include<cmath> 
#include<iostream> 
#define MAXN 200001
using namespace std;
struct node
{
	int l, r, highest;
}tree[4 * MAXN];

int a[MAXN], ans;
void build(int l, int r, int root)
{
	tree[root].l = l;
	tree[root].r = r;
	if (l == r)
	{
		tree[root].highest = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, root << 1); 
	build(mid + 1, r, root << 1 | 1);
	tree[root].highest = max(tree[root << 1].highest, tree[root << 1 | 1].highest); 
}
void update(int x, int y, int root)
{
	if (tree[root].l == tree[root].r)
	{
		tree[root].highest = y; return;
	}
	int mid = (tree[root].l + tree[root].r) >> 1;
	if (x <= mid)
		update(x, y, root << 1);
	else
		update(x, y, root << 1 | 1);
	tree[root].highest = max(tree[root << 1].highest, tree[root << 1 | 1].highest);
}
void query(int x, int y, int root)
{
	if (tree[root].l >= x&&tree[root].r <= y)
	{
		if (tree[root].highest>ans)ans = tree[root].highest;
		return;
	} 
	int mid = (tree[root].l + tree[root].r) >> 1;
	if (y <= mid)
		query(x, y, root << 1);//询问的区间在该区间的左区间内 
	else if (x>mid)
		query(x, y, root << 1 | 1);//询问的区间在该区间的右区间内 
	else//询问的区间横跨该区间的左右区间 
	{
		query(x, y, root << 1); query(x, y, root << 1 | 1);
	}
}
int main()
{
	int n, t, m, i, x, y, z;
	char s[3];
	while (~scanf("%d%d", &n, &m))
	{
		for (i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		build(1, n, 1);
		for (i = 1; i <= m; i++)
		{
			scanf("%s%d%d", s, &x, &y);
			if (s[0] == 'U')
				update(x, y, 1);
			else
			{
				ans = 0; query(x, y, 1); printf("%d\n", ans);
			}
		}
	}
	return 0;
}
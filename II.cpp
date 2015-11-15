#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int L[50005], R[50005], ind[50005], tree[50005], n, tick[50005], xxx = 0;
int ans[50005], Last[50005];
bool LR[50005];
int imax(int i, int j)
{
	if (ans[i] == ans[j]) return min(i, j);
	if (ans[i] < ans[j]) return j;
	return i;
}
inline int lowbit(int x) {return x & -x;}
void add(int x, int c)
{
	while (x <= n)
	{
		if (tick[x] < xxx)
		{
			tick[x] = xxx;
			tree[x] = 0;
		}
		tree[x] = imax(tree[x], c);
		x += lowbit(x);
	}
}
int query(int x)
{
	int res = 0;
	while (x)
	{
		if (tick[x] < xxx)
		{
			tick[x] = xxx;
			tree[x] = 0;
		}
		res = imax(res, tree[x]);
		x -= lowbit(x);
	}
	return res;
}
void fenwick(int len)
{
	/*printf("%d : ", len);
	for (int i = 1; i <= len; ++ i) printf("%d", LR[ind[i]]);
	puts("");*/
	xxx ++;
	for (int ii = len; ii >= 1; -- ii)
	{
		int i = ind[ii];
		if (LR[i])
		{
			add(R[i], i);
			//printf("add %d %d\n", R[i], i);
		}
		else
		{
			int tmp = query(R[i]);
			//printf("query %d = %d\n", R[i], tmp);
			if (ans[tmp] + 1 > ans[i] || (ans[tmp] + 1 == ans[i] && Last[i] > tmp))
			{
				Last[i] = tmp;
				ans[i] = ans[tmp] + 1;
				//printf("ooo last[%d] = %d\n", i, tmp);
				//printf("---%d  %d\n", i, ans[i]);
			}
		}
	}
}
bool cmp(int i, int j)
{
	return L[i] > L[j];
}
void cdq(int L, int R)
{
	if (L >= R) return;
	int mid = (L + R) / 2;
	cdq(mid + 1, R);
	int len = 0;
	for (int i = L; i <= mid; ++ i) ind[++ len] = i, LR[i] = 0;
	for (int i = mid + 1; i <= R; ++ i) ind[++ len] = i, LR[i] = 1;
	sort(ind + 1, ind + 1 + len, cmp);
	fenwick(len);
	cdq(L, mid);
}
int main()
{
	while (scanf("%d", &n) == 1)
	{
		for (int i = 1; i <= n; ++ i) scanf("%d", &L[i]);
		vector<int> g;
		for (int i = 1; i <= n; ++ i)
		{
			scanf("%d", &R[i]);
			R[i] = -R[i];
			g.push_back(R[i]);
		}
		sort(g.begin(), g.end());
		g.erase(unique(g.begin(), g.end()), g.end());
		for (int i = 1; i <= n; ++ i)
		{
			R[i] = lower_bound(g.begin(), g.end(), R[i]) - g.begin() + 1;
			//printf("$$$%d\n", R[i]);
		}
		ans[0] = 0;
		for (int i = 1; i <= n; ++ i)
		{
			ans[i] = 1;
			Last[i] = 0;
		}
		cdq(1, n);
		int A = 0, ind = 0;
		for (int i = 1; i <= n; ++ i)
		{
			//printf("()%d\n", Last[i]);
			if (A < ans[i])
			{
				A = ans[i];
				ind = i;
			}
		}
		printf("%d\n", A);
		for (int i = ind; i; i = Last[i]) printf("%d%c", i, " \n"[Last[i] == 0]);
	}
}
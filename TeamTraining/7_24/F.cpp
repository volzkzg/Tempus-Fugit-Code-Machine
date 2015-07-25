#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

const int MAXN = 1111111;

int L[MAXN], R[MAXN];
int now;
bool vis[MAXN];
void del(int x)
{
	vis[x] = true;
	L[R[x]] = L[x];
	R[L[x]] = R[x];
}

int f[MAXN];
int a[MAXN];

int main()
{
	int T;
	scanf("%d", &T);
	int iCase = 0;
	while(T--)
	{
		printf("Case #%d: ", ++iCase);
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
		{
			L[i] = i - 1;
			R[i] = i + 1;
		}
		L[0] = n - 1;
		R[n - 1] = 0;
		memset(f, 0, sizeof f);
		int u, v;
		for(int i = 0; i < m; ++i)
		{
			scanf("%d%d", &u, &v);
			a[u] = v;
			a[v] = u;
			f[u] = 1;
			f[v] = -1;
		}
		int now = 0;
		memset(vis, 0, sizeof vis);
		for(int i = 0; i < n; ++i)
			if(!f[i])
				del(i);
		while(m)
		{
			bool flag = false;
			while(vis[now]) now++;
			for(int i = now;;)
			{
				u = i, v = R[i];
				if(f[u] == f[v] && (R[a[u]] == a[v] || R[a[v]] == a[u]))
				{
					del(u), del(v);
					del(a[u]), del(a[v]);
					m -= 2;
					flag = true;
					break;
				}
				else if(a[u] == v)
				{
					del(u), del(v);
					m -= 1;
					flag = true;
					break;
				}
				if(R[i] < i) break;
				i = R[i];
			}
			if(!flag) break;
		}
		printf("%s\n", m ? "NO" : "YES");
	}
	return 0;
}
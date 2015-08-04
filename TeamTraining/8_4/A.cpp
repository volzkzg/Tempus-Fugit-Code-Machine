#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

void read(int &x)
{
	static char c = getchar();
	x = 0;
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
}

const int Maxn = 600, Maxm = 50000;

class Graph
{
public:
	int head[Maxn], Next[Maxm], No[Maxm], tot;
	void init(int n)
	{
		tot = 2;
		for(int i = 0; i <= n; ++i)
			head[i] = 0;
	}
	void add(int x, int y)
	{
		Next[tot] = head[x];
		head[x] = tot;
		No[tot++] = y;
	}
}G;

const int inf = 0x3f3f3f3f;

int n, m, ans;

void bfs(int st)
{
	static int q[Maxn];
	static int vis[Maxn];
	static int dis[Maxn];
	static bool visEdge[Maxm];
	for(int i = 0; i <= n; ++i)
		vis[i] = 0, dis[i] = inf;
	for(int i = 0; i <= G.tot; ++i)
		visEdge[i] = false;
	int l, r;
	l = r = -1;
	q[++r] = st; dis[st] = 0; vis[st] = 1;
	while(l < r)
	{
		int cur = q[++l];
		for(int i = G.head[cur]; i; i = G.Next[i])
		{
			if(visEdge[i]) continue;
			int y = G.No[i];
			vis[y]++;
			if(vis[y] == 1) //first 
			{
				q[++r] = y;
				dis[y] = dis[cur] + 1;
				visEdge[i] = visEdge[i ^ 1] = true;
			}
			if(vis[y] > 1 && visEdge[i] == false)
			{
				ans = min(ans, dis[cur] + dis[y] + 1);
			}
		}
	}
}

int main() 
{
	int T;
	read(T);
	for(int iCase = 1; iCase <= T; ++iCase)
	{
		printf("Case %d: ", iCase);
		scanf("%d%d", &n, &m);
		G.init(n);
		for(int i = 0; i < m; ++i)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			G.add(u, v);
			G.add(v, u);
		}
		ans = inf;
		for(int i = 0; i < n; ++i)
			bfs(i);
		if(ans == inf)
			printf("impossible\n");
		else
			printf("%d\n", ans);
	}
	return 0;
}

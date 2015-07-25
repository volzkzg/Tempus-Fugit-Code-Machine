#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <queue>
using namespace std;

int n, m;

const int Maxn = 10000, Maxm = 300000;

int S, T;

class Graph
{
public:
	int head[Maxn], Next[Maxm], No[Maxm];
	long long w[Maxm]; int flow[Maxm];
	int tot;
	void init(int n)
	{
		tot = 2;
		for(int i = 0; i <= n + 2; ++i)
			head[i] = 0;
	}
	void add(int x, int y, long long len, int f)
	{
		Next[tot] = head[x];
		head[x] = tot;
		No[tot] = y;
		w[tot] = len;
		flow[tot++] = f;
	}
	void addedge(int x, int y, long long len, int f)
	{
		add(x, y, len, f);
		add(y, x, len, 0);
	}
}G, flowG;

long long mindst[Maxn];
bool inq[Maxn];

void spfa()
{
	queue<int> q;
	q.push(1);
	for(int i = 1; i <= n; ++i)
		mindst[i] = 1LL << 60;
	mindst[1] = 0;
	while(!q.empty())
	{
		int cur = q.front(); q.pop();
		inq[cur] = false;
		for(int i = G.head[cur]; i; i = G.Next[i])
		{
			int y = G.No[i];
			if(mindst[y] > mindst[cur] + G.w[i])
			{
				mindst[y] = mindst[cur] + G.w[i];
				if(!inq[y])
					inq[y] = true, q.push(y);
			}
		}
	}
}

const int Mod = 1000000000;

int d[Maxn];
int q[Maxn];

bool bfs()
{
	int l, r;
	l = r = -1;
	q[++r] = S;
	for(int i = 1; i <= n; ++i)
		d[i] = -1;
	d[S] = 0;
	while(l < r)
	{
		int cur = q[++l];
		for(int i = flowG.head[cur]; i; i = flowG.Next[i])
		{
			int y = flowG.No[i];
			if(flowG.flow[i] == 0) continue;
			if(d[y] == -1)
			{
				d[y] = d[cur] + 1;
				q[++r] = y;
			}
		}
	}
	return d[T] != -1;
}

int dfs(int cur, int flow)
{
	if(flow == 0 || cur == T) return flow;
	int orig = flow;
	for(int i = flowG.head[cur]; i; i = flowG.Next[i])
	{
		int y = flowG.No[i];
		if(d[y] != d[cur] + 1) continue;
		int t = dfs(y, min(flow, flowG.flow[i]));
		flowG.flow[i] -= t;
		flowG.flow[i ^ 1] += t;
		flow -= t;
		if(flow == 0)
			return orig;
	}
	d[cur] = -1;
	return orig - flow;
}

int dinic()
{
	int ret = 0;
	while(bfs())
		ret += dfs(1, Mod);
	return ret;
}

int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		G.init(n);
		flowG.init(n);
		for(int i = 0; i < m; ++i)
		{
			int a, b, l;
			scanf("%d%d%d", &a, &b, &l);
			G.addedge(a, b, l, 0);
		}
		spfa();
		S = 1, T = n;
		for(int i = 1; i <= n; ++i)
		{
			for(int j = G.head[i]; j; j = G.Next[j])
			{
				int y = G.No[j];
				if(mindst[i] + G.w[j] == mindst[y])
					flowG.addedge(i, y, 0, 1);
			}
		}
		int flow = dinic();
		for(int i = 2; i < G.tot; ++i)
			G.w[i] = G.w[i] * Mod + 1;
		spfa();
		int num = mindst[n] % Mod;
		printf("%d %d\n", flow, m - num);
	}
	return 0;
}

#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 100000 + 10;
const int M = 20;

int T, n, m, times;
vector<int> g[N];
vector<int> lst[N];
int pre[N][M], deep[N], st[N], ed[N];
int dp[N], sum[N], tree[N * 2];
struct node {
	int u, v, p;
	void read() {
		scanf("%d%d%d", &u, &v, &p);
	}
} chain[N];

inline void add(int pos, int val)
{
	for (int i = pos; i <= times; i += i & (-i))
		tree[i] += val;
}

inline int qry(int pos)
{
	int ret = 0;
	for (int i = pos; i > 0; i -= i & (-i))
		ret += tree[i];
	return ret;
}

void lca_dfs(int u, int fa)
{
	if (fa == -1) deep[u] = 1;
	else deep[u] = deep[fa] + 1;
	pre[u][0] = fa;
	for (int i = 0; i < (int)g[u].size(); ++i) {
		int v = g[u][i];
		if (v == fa) continue;
		lca_dfs(v, u);
	}
}

void init_lca()
{
	//init array
	for (int j = 0; (1 << j) <= n; ++j)
		for (int i = 1; i <= n; ++i)
			pre[i][j] = -1;
	lca_dfs(1, -1);
	for (int j = 1; (1 << j) <= n; ++j)
		for (int i = 1; i <= n; ++i)
			if (pre[i][j - 1] != -1)
				pre[i][j] = pre[pre[i][j - 1]][j - 1];
}

int get_lca(int u, int v)
{
	int step;
	if (deep[u] < deep[v]) swap(u, v);
	for (step = 0; (1 << step) <= deep[u]; ++step);
	step--;
	
	for (int i = step; i >= 0; --i)
		if (deep[u] - (1 << i) >= deep[v])
			u = pre[u][i];
	if (u == v) return u;

	for (int i = step; i >= 0; --i) {
		if (pre[u][i] != -1 && pre[u][i] != pre[v][i]) {
			u = pre[u][i];
			v = pre[v][i];
		}
	}
	return pre[u][0];
}

void dfn_dfs(int u, int fa)
{
	st[u] = ++times;
	for (int i = 0; i < (int)g[u].size(); ++i) {
		int v = g[u][i];
		if (v == fa) continue;
		dfn_dfs(v, u);
	}
	ed[u] = ++times;
}

void get_dfn()
{
	times = 0;
	dfn_dfs(1, -1);
}

void init()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		g[i].clear();
		lst[i].clear();
		dp[i] = sum[i] = 0;
	}
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	init_lca();
	get_dfn();
	
	for (int i = 1; i <= m; ++i) {
		chain[i].read();
		int lca = get_lca(chain[i].u, chain[i].v);
		lst[lca].push_back(i);
	}

	for (int i = 0; i <= times + 10; ++i)
		tree[i] = 0;
}

void dp_dfs(int u, int fa)
{
	for (int i = 0; i < (int)g[u].size(); ++i) {
		int v = g[u][i];
		if (v == fa) continue;
		dp_dfs(v, u);
		sum[u] += dp[v];
	}
	dp[u] = sum[u];
	for (int i = 0; i < (int)lst[u].size(); ++i) {
		int id = lst[u][i];
		int lhs = chain[id].u;
		int rhs = chain[id].v;
		int val = chain[id].p;
		dp[u] = max(dp[u], val + qry(st[lhs]) + qry(st[rhs]) + sum[u]);
	}
	add(st[u], sum[u] - dp[u]);
	add(ed[u], dp[u] - sum[u]);
	//cout << u << " " << dp[u] << " " << sum[u] << endl;
}

void solve()
{
	dp_dfs(1, -1);
	cout << dp[1] << endl;
}

int main()
{
	scanf("%d", &T);
	while (T--) {
		init();
		solve();
	}
	
	return 0;
}

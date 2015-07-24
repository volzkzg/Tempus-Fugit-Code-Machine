#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 220000 + 10;

int tst_case;
int n, m;
int dfn[MAXN], low[MAXN], bccno[MAXN], dfn_clock, bcc_cnt, Top;
vector <int> G[MAXN], bcc[MAXN], g[MAXN];
pair <int, int> stk[MAXN];

void dfs(int p, int fa) {
	low[p] = dfn[p] = ++dfn_clock;
	for (int i = 0; i < G[p].size(); ++i) {
		int v = G[p][i];
		if (!dfn[v]) {
			stk[++Top] = make_pair(p, v);
			dfs(v, p);
			low[p] = min(low[p], low[v]);
			if (low[v] >= dfn[p]) {
				++bcc_cnt;
				bcc[bcc_cnt].clear();
				for (;;) {
					pair <int, int> x = stk[Top];
					--Top;
					if (bccno[x.first] != bcc_cnt) {
						bccno[x.first] = bcc_cnt;
						bcc[bcc_cnt].push_back(x.first);
					}
					if (bccno[x.second] != bcc_cnt) {
						bccno[x.second] = bcc_cnt;
						bcc[bcc_cnt].push_back(x.second);
					}
					if (x.first == p && x.second == v)
						break;
				}
			}
		}
		else
			if (dfn[v] < dfn[p] && v != fa) {
				stk[++Top] = make_pair(p, v);
				low[p] = min(low[p], dfn[v]);
			}
	}
}

void find_bcc(int n) {
	for (int i = 1; i <= n; ++i)
		dfn[i] = bccno[i] = 0;
	dfn_clock = bcc_cnt = 0;
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])
			dfs(i, -1);
}

int cnt, ans;
int idx[MAXN];
bool vis[MAXN];

void dfs2(int p, int fa) {
	++cnt;
	vis[p] = 1;
	for (int i = 0; i < g[p].size(); ++i) {
		int v = g[p][i];
		if (v == fa) continue;
		if (vis[v] == 1) continue;
		dfs2(v, p);
	}
}

int main() {
	int tt = 0;
	scanf("%d", &tst_case);
	while (tst_case--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			G[i].clear();
		for (int a, b, i = 1; i <= m; ++i) {
			scanf("%d%d", &a, &b);
			G[a].push_back(b);
			G[b].push_back(a);
		}
	        find_bcc(n);
		for (int i = 1; i <= n; ++i)
			g[i].clear();
		for (int i = 1; i <= n; ++i)
			idx[i] = 0;
	        for (int i = 1; i <= bcc_cnt; ++i)
			if (bcc[i].size() > 2) {
				for (int j = 0; j < bcc[i].size(); ++j)
					idx[bcc[i][j]] = -1;
			}
		for (int p = 1; p <= n; ++p)
			if (idx[p] != -1) 
				for (int i = 0; i < G[p].size(); ++i) {
					int v = G[p][i];
					if (idx[v] == -1) continue;
					g[p].push_back(v);
				}
		for (int i = 1; i <= n; ++i)
			vis[i] = 0;
		ans = 0;
		for (int i = 1; i <= n; ++i)
			if (!vis[i] && idx[i] != -1) {
				cnt = 0;
				dfs2(i, -1);
				ans += cnt * (cnt - 1) / 2;
			}
		printf("Case #%d: %d\n", ++tt, ans);
	}

	return 0;
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int N = 111111;
const int INF = 0x7FFFFFFF/2;
vector<pair<int, int> > g[N];
set<int> st;
int n, q, dist[N], fa[N], deep[N], times, dfn[N], redfn[N], anc[N][20];

void init()
{
	st.clear();
	for (int i = 1; i <= n; ++i) {
		g[i].clear();
		dist[i] = 0;
	}
	deep[0] = 0;
	times = 0;
}

void dfs(int u, int pre)
{
	//cout << u << " " << pre << endl;
	fa[u] = pre;
	deep[u] = deep[pre] + 1;
	dfn[u] = ++times;
	redfn[times] = u;
	for (int i = 0; i < (int)g[u].size(); ++i) {
		int v = g[u][i].first;
		int w = g[u][i].second;
		if (v == pre) continue;
		dist[v] = dist[u] + w;
		dfs(v, u);
	}
}

void process()
{
	for (int i = 1; i <= n; ++i) {
		anc[i][0] = fa[i];
		for (int j = 1; (1 << j) <= n; ++j)
			anc[i][j] = -1;
	}
	for (int j = 1; (1 << j) <= n; ++j)
		for (int i = 1; i <= n; ++i) {
			if (anc[i][j - 1] != -1) {
				int a = anc[i][j - 1];
				anc[i][j] = anc[a][j - 1];
			}
		}
}

int lca(int p, int q)
{
	int tmp, Log, i;
	if (deep[p] < deep[q]) swap(p, q);
	for (Log = 1; (1 << Log) <= deep[p]; ++Log);
	Log--;
	for (int i = Log; i >= 0; --i)
		if (deep[p] - (1 << i) >= deep[q]) 
			p = anc[p][i];
	if (p == q) return p;
	for (int i = Log; i >= 0; i--)
		if (anc[p][i] != -1 && anc[p][i] != anc[q][i]) {
			p = anc[p][i];
			q = anc[q][i];
		}
	return fa[p];
}

int main()
{
	int T, tst = 0;
	scanf("%d", &T);
	while (T--) {
		printf("Case #%d:\n", ++tst);
		scanf("%d%d", &n, &q);
		init();
		for (int i = 1; i < n; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			g[u].push_back(make_pair(v, w));
			g[v].push_back(make_pair(u, w));
		}
		dfs(1, 0);
		process();
		int ans = 0;
		/*
		  if (tst == 1) {
		  cout << lca(7, 8) << endl;
		  cout << lca(12, 2) << endl;
		  cout << lca(14, 10) << endl;
		  }
		*/
		for (int i = 1; i <= q; ++i) {
			int mode, u, x, y;
			scanf("%d%d", &mode, &u);
			if (mode == 1) {
				if (st.find(dfn[u]) == st.end()) {
					if ((int)st.size() == 0) {
						st.insert(dfn[u]);
					} else {
						if (dfn[u] < (*st.begin())) {
							x = *st.begin();
							y = *st.rbegin();
							//ans += dist[u] - dist[lca(redfn[*st.begin()], u)];
						} else if (dfn[u] > (*st.rbegin())) {
							x = *st.begin();
							y = *st.rbegin();
							//ans += dist[u] - dist[lca(redfn[*st.rbegin()], u)];
						} else {
							//set<int>::iterator iter = lower_bound(st.begin(), st.end(), dfn[u]);
							set<int>::iterator iter = st.lower_bound(dfn[u]);
							y = *iter; iter--;
							x = *iter;
						}
						x = redfn[x];
						y = redfn[y];
						//cout << x << " " << y << endl;
						ans += dist[u] - dist[lca(x, u)] - dist[lca(y, u)] + dist[lca(x, y)];
						st.insert(dfn[u]);
					}
				}
			} else {
				if (st.find(dfn[u]) != st.end()) {
					if ((int)st.size() == 1) {
						st.erase(dfn[u]);
					} else {
						if (dfn[u] == (*st.begin())) {
							set<int>::iterator iter;
							iter = st.begin();
							iter++;
							x = *iter;
							y = *st.rbegin();
						} else if (dfn[u] == (*st.rbegin())) {
							set<int>::reverse_iterator iter;
							iter = st.rbegin();
							iter--;
							y = *iter;
							x = *st.begin();
						} else {
							set<int>::iterator iter;
							iter = st.find(dfn[u]);
							iter--;
							x = *iter;
							iter++; iter++;
							y = *iter;
						}
						x = redfn[x];
						y = redfn[y];
						ans -= dist[u] - dist[lca(x, u)] - dist[lca(y, u)] + dist[lca(x, y)];
						st.erase(dfn[u]);
					}
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}

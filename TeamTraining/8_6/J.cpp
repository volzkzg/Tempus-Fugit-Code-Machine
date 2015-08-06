#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const int MAXN = 2000 + 10;
const int MAXM = MAXN * MAXN / 4;
const int INF = 0x7FFFFFFF >> 2;

struct Edge {
	int next, to, w;
} g[MAXM];
int gn, start[MAXN], now[MAXN];

inline void AddEdge(int a, int b, int c) {
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
	gn++; g[gn].next = start[b]; start[b] = gn; g[gn].to = a; g[gn].w = 0;
}

int n, m, S, T, h[MAXN], vh[MAXN], N;
vector <int> ed[MAXN];

int Aug(int p, int flow) {
	if (p == T)
		return flow;
	int ret = flow;
	for (int i = now[p]; i; now[p] = i = g[i].next) {
		int v = g[i].to;
		if (g[i].w <= 0)
			continue;
		if (h[p] != h[v] + 1)
			continue;
		int tmp = Aug(v, min(g[i].w, ret));
		ret -= tmp;
		g[i].w -= tmp;
		g[i ^ 1].w += tmp;
		if (ret == 0)
			return flow;
	}
	--vh[h[p]];
	if (vh[h[p]] == 0)
		h[S] = N;
	++h[p]; ++vh[h[p]];
	now[p] = start[p];
	return flow - ret;
}

string str;

bool check(int x) {
	gn = 1;
	for (int i = 1; i <= N; ++i)
		start[i] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < (int)ed[i].size(); ++j)
			AddEdge(ed[i][j], i + m, 1);
	}
	for (int i = 1; i <= n; ++i)
		AddEdge(i + m, T, 1);
	for (int i = 1; i <= m; ++i)
		AddEdge(S, i, x);
	for (int i = 1; i <= N; ++i)
		h[i] = vh[i] = 0;
	for (int i = 1; i <= N; ++i)
		now[i] = start[i];
	vh[0] = N;
	int maxflow = 0;
	while (h[S] < N)
		maxflow += Aug(S, INF);
	if (maxflow == n)
		return true;
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	while (cin >> n >> m) {
		if (n == 0 && m == 0)
			break;
		gn = 1;
		S = n + m + 1; T = S + 1; N = T;
		getline(cin, str);
		for (int i = 1; i <= n; ++i)
			ed[i].clear();
		for (int i = 1; i <= n; ++i) {
			string name;
			getline(cin, str);
			istringstream read(str);
			read >> name;
			int x;
			while (read >> x) {
				++x;
				ed[i].push_back(x);
			}
		}
		int l = 1, r = n, ans;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				ans = mid;
				r = mid - 1;
			}
			else
				l = mid + 1;
		}
		cout << ans << endl;
	}

	return 0;
}

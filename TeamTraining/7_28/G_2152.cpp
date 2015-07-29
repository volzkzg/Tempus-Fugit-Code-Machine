#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

const int Maxn = 1100;

int w[Maxn], need[Maxn], n;
vector<pair<int, int> > nxt[Maxn], ch[Maxn];
int q[Maxn], fa[Maxn];
int dst[Maxn][Maxn];
bool child[Maxn][Maxn];
int f[Maxn][Maxn], minf[Maxn];

void initDst(int S, int pre, int tot, int *dst) {
	dst[S] = tot;
	for(int i = 0; i < nxt[S].size(); ++i) {
		int y = nxt[S][i].first;
		if(y == pre) continue;
		initDst(y, S, tot + nxt[S][i].second, dst);
	}
}

void init() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		nxt[i].clear(), ch[i].clear(), fa[i] = -1;
		for(int j = 0; j < n; ++j)
			child[i][j] = false;
	}
	for(int i = 0; i < n; ++i)
		scanf("%d", w + i);
	for(int i = 0; i < n; ++i)
		scanf("%d", need + i);
	for(int i = 0; i < n - 1; ++i) {
		int x, y, d;
		scanf("%d%d%d", &x, &y, &d);
		x--, y--;
		nxt[x].push_back(make_pair(y, d)), nxt[y].push_back(make_pair(x, d));
	}
	int l, r;
	l = r = -1;
	q[++r] = 0;
	while(l < r) {
		int cur = q[++l];
		for(int i = 0; i < (int)nxt[cur].size(); ++i) {
			int y = nxt[cur][i].first;
			if(y == fa[cur]) continue;
			ch[cur].push_back(nxt[cur][i]), q[++r] = y;
			fa[y] = cur;
		}
	}
	for(int i = n - 1; i >= 0; --i) {
		child[q[i]][q[i]] = true;
		for(int j = 0; j < ch[q[i]].size(); ++j)
			for(int k = 0; k < n; ++k)
				child[q[i]][k] |= child[ch[q[i]][j].first][k];
	}
	for(int i = 0; i < n; ++i) {
		initDst(i, -1, 0, dst[i]);
	//	for(int j = 0; j < n; ++j)
	//		printf("dist[%d][%d] = %d\n", i, j, dst[i][j]);
	}
/*	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j)
			printf("child[%d][%d] = %d\n", i, j, child[i][j]);
	}
*/
	for(int i = 0; i < n; ++i) {
		minf[i] = 0x3f3f3f3f;
		for(int j = 0; j <= n; ++j)
			f[i][j] = 0x3f3f3f3f;
	}
}

void solve() {
	for(int p = n - 1; p >= 0; --p) {
		int i = q[p];
		for(int j = 0; j < n; ++j) {
			if(dst[j][i] > need[i])
				f[i][j] = 0x3f3f3f3f;
			else {
				f[i][j] = w[j];
				for(int k = 0; k < ch[i].size(); ++k) {
					int y = ch[i][k].first;
					f[i][j] += min(minf[y], f[y][j] - w[j]);
				}
				minf[i] = min(minf[i], f[i][j]);
			}
		}
	}
	int ans = 0x3f3f3f3f;

/*	for(int i = 0; i < n; ++i)
		for(int j = 0; j <= n; ++j)
			printf("f[%d][%d] = %d\n", i, j, f[i][j]);*/

	for(int j = 0; j < n; ++j)
		ans = min(ans, f[0][j]);

	printf("%d\n", ans);
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		init();
		solve();
	}
	return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

const int MAXN = 100000 + 10;

vector <int> G[MAXN];
int n, m;
long long w[MAXN], s[MAXN];
bool vis[MAXN];

void dfs(int p) {
	s[p] += w[p];
	vis[p] = 1;
	for (int i = 0; i < G[p].size(); ++i) {
		int v = G[p][i];
		if (vis[v])
			continue;
		dfs(v);
		s[p] += s[v];
	}
}

int main() {
	int tt = 0;
	while (scanf("%d%d", &n, &m) == 2) {
		if (n == 0 && m == 0)
			break;
		for (int i = 1; i <= n; ++i)
			G[i].clear();
		for (int i = 1; i <= n; ++i)
			scanf("%lld", &w[i]);
		long long sum = 0;
		for (int i = 1; i <= n; ++i)
			sum += w[i];
		for (int a, b, i = 1; i <= m; ++i) {
			scanf("%d%d", &a, &b);
			G[a].push_back(b);
			G[b].push_back(a);
		}
		for (int i = 1; i <= n; ++i)
			s[i] = 0;
		for (int i = 1; i <= n; ++i)
			vis[i] = 0;
		dfs(1);
		long long ans = 1000000000000000000LL;
		for (int i = 1; i <= n; ++i) {
		        long long cur = s[i] - (sum - s[i]);
			if (cur < 0)
				cur = -cur;
			ans = min(ans, cur);
		}
		printf("Case %d: %lld\n", ++tt, ans);
	}

	return 0;
}

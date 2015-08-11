#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 500000 + 10;

int n;
vector <int> G[MAXN];
int ind[MAXN], w[MAXN];
int s[MAXN];
vector <int> Q;

int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; ++i)
			scanf("%d", &w[i]);
		for (int i = 1; i <= n; ++i)
			ind[i] = s[i] = 0;
		for (int i = 1; i <= n; ++i)
			G[i].clear();
		for (int a, b, i = 1; i < n; ++i) {
			scanf("%d%d", &a, &b);
			if (w[a] < w[b])
				swap(a, b);
			ind[b]++;
			G[a].push_back(b);
		}
		Q.clear();
		for (int i = 1; i <= n; ++i)
			if (!ind[i])
				Q.push_back(i);
		int ans = 0;
		for (int head = 0; head < (int)Q.size(); ++head) {
			int p = Q[head];
			s[p]++;
			ans = max(ans, s[p]);
			for (int i = 0; i < (int)G[p].size(); ++i) {
				int v = G[p][i];
				s[v] += s[p];
				--ind[v];
				if (ind[v] == 0)
					Q.push_back(v);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

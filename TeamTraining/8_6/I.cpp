#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int MAXS = (1 << 14) + 10;
const int MAXN = 15;

long long f[MAXS][MAXN][MAXN], w[MAXN];
int n, tst_case, m;
int map[MAXN][MAXN];
long long g[MAXS][MAXN][MAXN];

int main() {
	ios::sync_with_stdio(false);
	cin >> tst_case;
	while (tst_case--) {
		cin >> n >> m;
		for (int i = 0; i < n; ++i)
			cin >> w[i];
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				map[i][j] = 0;
		for (int a, b, i = 1; i <= m; ++i) {
			cin >> a >> b;
			--a; --b;
			map[a][b] = map[b][a] = 1;
		}
		if (n == 1) {
			cout << w[0] << ' ' << 1 << endl;
			continue;
		}
		memset(f, -1, sizeof(f));
		memset(g, 0, sizeof(g));
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j) {
				if (i == j) continue;
				if (map[i][j] == 0) continue;
				f[(1 << i) + (1 << j)][i][j] = w[i] + w[j] + w[i] * w[j];
				g[(1 << i) + (1 << j)][i][j] = 1;
			}
		for (int s = 0; s < (1 << n); ++s)
			for (int i = 0; i < n; ++i) {
				if ((s & (1 << i)) == 0)
					continue;
				for (int j = 0; j < n; ++j) {
					if ((s & (1 << j)) == 0 || i == j || map[i][j] == 0)
						continue;
					if (f[s][i][j] == -1)
						continue;
					for (int k = 0; k < n; ++k) {
						if (i == k || j == k || (s & (1 << k)) != 0 || map[j][k] == 0)
							continue;
						long long tmp = f[s][i][j] + w[k] + w[k] * w[j];
						if (map[i][k]) {
							tmp += w[k] * w[j] * w[i];
						}
						int nw = s + (1 << k);
						if (tmp > f[nw][j][k]) {
							f[nw][j][k] = tmp;
							g[nw][j][k] = g[s][i][j];
						}
						else if (tmp == f[nw][j][k]) {
							g[nw][j][k] += g[s][i][j];
						}
					}
				}
			}
		long long ans1 = -1;
		long long ans2 = 0;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (ans1 < f[(1 << n) - 1][i][j]) {
					ans1 = f[(1 << n) - 1][i][j];
					ans2 = g[(1 << n) - 1][i][j];
				}
				else if (ans1 == f[(1 << n) - 1][i][j]) {
					ans2 += g[(1 << n) - 1][i][j];
				}
		if (ans1 != -1)
			cout << ans1 << ' ' << ans2 / 2 << endl;
		else
			cout << 0 << ' ' << 0 << endl;
	}
	return 0;
}

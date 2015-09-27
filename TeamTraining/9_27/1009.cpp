#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 40;
const int INF = 0x7FFFFFFF/2;
int T, n, m, a[N][N], s[N][N], f[N][N][N * 60];

int main()
{
	scanf("%d\n", &T);
	for (int tst = 1; tst <= T; ++tst) {
		printf("Case #%d: ", tst);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &a[i][j]);
				s[i][j] = a[i][j] * a[i][j];
			}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				for (int k = 0; k <= 30 * (n + m); ++k)
					f[i][j][k] = INF;
		f[1][1][a[1][1]] = s[1][1];
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				for (int k = 0; k <= 30 * (n + m); ++k) {
					if (f[i][j][k] == INF) continue;
					int &now = f[i][j][k];
					if (j + 1 <= m) {
						int &next = f[i][j + 1][k + a[i][j + 1]];
						next = min(next, now + s[i][j + 1]);
					}
					if (i + 1 <= n) {
						int &next = f[i + 1][j][k + a[i + 1][j]];
						next = min(next, now + s[i + 1][j]);
					}
				}
		int ans = INF;
		for (int k = 0; k <= 30 * (n + m); ++k) {
			if (f[n][m][k] == INF) continue;
			ans = min(ans, (n + m - 1) * f[n][m][k] - k * k);
		}
		printf("%d\n", ans);
	}
	return 0;
}

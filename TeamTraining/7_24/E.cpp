#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 50 + 10;
const int MAXM = 2000 + 10;
const int INF = 0x7FFFFFFF >> 2;

int n, tst_case, H, W, p[MAXN], h[MAXN];
int f[MAXN][MAXM];
bool iss[MAXN];

int main() {
	int tt = 0;
	scanf("%d", &tst_case);
	while (tst_case--) {
		scanf("%d%d%d", &n, &H, &W);
		printf("Case #%d: ", ++tt);
		int maxh = 0, ans = INF;
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &p[i], &h[i]);
			maxh = max(maxh, h[i]);
		}
		for (int i = 1; i <= n; ++i)
			iss[i] = 0;
		for (int i = 1; i <= n; ++i)
			if (maxh == h[i])
				iss[i] = 1;
		for (int i = 0; i <= n + 1; ++i)
			for (int j = 1; j <= 500; ++j)
				f[i][j] = INF;
		for (int i = 1; i <= n; ++i)
			if (!iss[i])
				for (int j = 1; j <= 500; ++j) {
					if (h[i] <= H)
						f[i][j] = 0;
					else if (h[i] <= h[i - 1] + H)
						for (int k = max(j - W, 1); k < j; ++k) {
							f[i][j] = min(f[i - 1][k], f[i][j]);
						}
					if (f[i][j] < INF)
						f[i][j] += (abs(p[i] - j)) * h[i];
				}
			else {
				if (h[i] <= H)
					f[i][p[i]] = 0;
				else if (h[i] <= h[i - 1] + H)
					for (int k = max(p[i] - W, 1); k < p[i]; ++k) {
						f[i][p[i]] = min(f[i - 1][k], f[i][p[i]]);
					}
       
			}
		for (int i = 1; i <= n; ++i)
			if (iss[i])
				ans = min(ans, f[i][p[i]]);

		for (int i = 0; i <= n + 1; ++i)
			for (int j = 1; j <= 500; ++j)
				f[i][j] = INF;
		for (int i = n; i; --i)
			if (!iss[i])
				for (int j = 1; j <= 500; ++j) {
					if (h[i] <= H)
						f[i][j] = 0;
					else if (h[i] <= h[i + 1] + H)
						for (int k = min(j + W, 500); k > j; --k) {
							f[i][j] = min(f[i + 1][k], f[i][j]);
						}
					if (f[i][j] < INF)
						f[i][j] += (abs(j - p[i])) * h[i];
				}
			else {
				if (h[i] <= H)
					f[i][p[i]] = 0;
				else if (h[i] <= h[i + 1] + H)
					for (int k = min(p[i] + W, 500); k > p[i]; --k) {
						f[i][p[i]] = min(f[i + 1][k], f[i][p[i]]);
					}
       
			}
		for (int i = 1; i <= n; ++i)
			if (iss[i])
				ans = min(ans, f[i][p[i]]);
		if (ans > INF / 2) puts("-1");
		else printf("%d\n", ans);
	}

	return 0;
}

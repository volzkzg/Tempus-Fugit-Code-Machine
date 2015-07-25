#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;
const int MAXL = 21;

int n, k, a[MAXN];
int Log[MAXN];
int minx[MAXL][MAXN], maxx[MAXL][MAXN];

void Prepare() {
	memset(minx, 0, sizeof(minx));
	memset(maxx, 0, sizeof(maxx));
	for (int i = 1; i <= n; ++i)
		minx[0][i] = maxx[0][i] = a[i];
	for (int i = 1; i <= Log[n]; ++i) {
		for (int j = 1; j <= n - (1 << i) + 1; ++j) {
			minx[i][j] = min(minx[i - 1][j], minx[i - 1][j + (1 << (i - 1))]);
			maxx[i][j] = max(maxx[i - 1][j], maxx[i - 1][j + (1 << (i - 1))]);
		}
	}
}

int Query_min(int l, int r) {
	int lo = Log[r - l + 1];
	return min(minx[lo][l], minx[lo][r - (1 << lo) + 1]);
}

int Query_max(int l, int r) {
        int lo = Log[r - l + 1];
	return max(maxx[lo][l], maxx[lo][r - (1 << lo) + 1]);
}

bool check(int l, int r) {
	return Query_max(l, r) - Query_min(l, r) < k;
}

int main() {
	Log[1] = 0;
	for (int i = 2; i < MAXN; ++i)
		Log[i] = Log[i >> 1] + 1;
	int tst_case;
	scanf("%d", &tst_case);
	while (tst_case--) {
		long long ans = 0;
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		Prepare();
		for (int x = 1; x <= n; ++x) {
			int l = 1, r = x, curans;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (check(mid, x)) {
					r = mid - 1;
					curans = mid;
				}
				else
					l = mid + 1;
			}
			ans += (long long)(x - curans + 1);
		}
		cout << ans << endl;
	}

	return 0;
}

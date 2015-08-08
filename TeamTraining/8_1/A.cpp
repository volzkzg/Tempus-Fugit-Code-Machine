#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 200000 + 10;
const int MAXC = 63;

int cnt[MAXN << 1];
long long rnk[MAXN << 1];
int n;
long long a[MAXN], f[2][MAXN];

void radixsort(int x) {
	for (int i = 0; i <= n * 2; ++i)
		cnt[i] = 0;
	for (int i = 0; i < n; ++i) {
		rnk[i] = rnk[i + n] = a[i];
		if (a[i] >> x & 1)
			++cnt[i + n];
		else
			++cnt[i];
	}
	int len = 0;
	for (int i = 0; i < 2 * n; ++i)
		if (cnt[i])
			a[len++] = rnk[i];
	for (int i = 1; i <= 2 * n; ++i)
		cnt[i] += cnt[i - 1];
}

long long spj() {
	long long mi = (1LL << 62);
	for (int i = 0; i < n; ++i)
		mi = min(mi, a[i]);
	long long ret = 0;
	for (int i = 0; i < n; ++i)
		ret ^= (a[i] - mi);
	return (ret == 0);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
        int cur = 0, nxt = 1;
	f[nxt][0] = 1;
	for (int i = 0; i < MAXC; ++i) {
		cur ^= 1; nxt ^= 1;
		memset(f[nxt], 0, sizeof(f[nxt]));
		radixsort(i);
		int cursum = 0;
		for (int j = 0; j < n; ++j) 
			cursum ^= a[j] >> i & 1;
		for (int j = 0; j <= n; ++j) {
			if (f[cur][j] == 0) 
				continue;
	
			int newj = (j == 0) ? 0 : cnt[j - 1];
			if (~(cursum ^ j) & 1) {
				f[nxt][newj] += f[cur][j];
			}

			newj = (j == 0) ? cnt[n - 1] : cnt[j + n - 1];
			if (~(cursum ^ j ^ n) & 1) {
				f[nxt][newj] += f[cur][j];
			}
		}
	}
	cout << f[nxt][0] - spj() << endl;

	return 0;
}

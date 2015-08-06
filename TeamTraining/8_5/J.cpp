#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 1000 + 10;
const int INF = 0x7FFFFFFF >> 2;

int x[MAXN], y[MAXN];
int n;
int f[MAXN][MAXN];

int calc(int a, int b, int c, int d) {
	return abs(x[a] - x[c]) + abs(y[b] - y[d]);
}

int dp(int l, int r) {
	if (l == r)
		return 0;
	if (f[l][r] != -1)
		return f[l][r];
	int &ret = f[l][r];
	ret = INF;
	for (int k = l; k < r; ++k)
		ret = min(ret, dp(l, k) + dp(k + 1, r) + calc(l, k, k + 1, r));
	return ret;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d", &x[i], &y[i]);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			f[i][j] = -1;
	printf("%d\n", dp(1, n));

	return 0;
}

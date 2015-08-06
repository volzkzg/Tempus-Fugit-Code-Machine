#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 10;
const int INF = 0x7FFFFFFF >> 2;

int n, a[MAXN][MAXN];
int sum[MAXN], ans;

void check() {
	for (int i = 1; i <= n; ++i)
		sum[i] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			sum[i] += a[j][i];
	int tmp = -INF;
	for (int i = 1; i <= n; ++i)
		tmp = max(tmp, sum[i]);
	ans = min(ans, tmp);
}

void Shift(int x) {
	int tmp = a[x][n];
	for (int i = n; i >= 2; --i)
		a[x][i] = a[x][i - 1];
	a[x][1] = tmp;
}

void dfs(int deep) {
	check();
	if (deep == n)
		return;
	for (int i = 1; i <= n; ++i) {
		Shift(deep);
		dfs(deep + 1);
	}
}

int main() {
	while (scanf("%d", &n) == 1) {
		if (n == -1)
			break;
		ans = INF;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				scanf("%d", &a[i][j]);
		dfs(1);
		printf("%d\n", ans);
	}
	
	return 0;
}

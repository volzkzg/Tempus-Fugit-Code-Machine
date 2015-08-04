#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 100 + 10;
const int dx[2] = {0, 1};
const int dy[2] = {1, 0};

int tst_case;
int n, m, p, q;
int map[MAXN][MAXN];
bool vis[MAXN][MAXN];

bool check(int x, int y) {
	return (x > 0 && x <= n && y > 0 && y <= m && map[x][y] != 2);
}

int calc(int x, int y, int d) {
	int ret = 1;
	for (;;) {
		x += dx[d];
		y += dy[d];
		if (!check(x, y))
			break;
		if (map[x][y] == 1)
			++ret;
	}
	return ret;
}

void cover(int x, int y, int d) {
	vis[x][y] = 1;
	for (;;) {
		x += dx[d];
		y += dy[d];
		if (!check(x, y))
			break;
		vis[x][y] = 1;
	}
}

int main() {
	scanf("%d", &tst_case);
	while (tst_case--) {
		scanf("%d%d", &n, &m);
		scanf("%d", &p);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				map[i][j] = 0;
		for (int a, b, i = 1; i <= p; ++i) {
			scanf("%d%d", &a, &b);
			map[a][b] = 1;
		}
		scanf("%d", &q);
		for (int a, b, i = 1; i <= q; ++i) {
			scanf("%d%d", &a, &b);
			map[a][b] = 2;
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				vis[i][j] = 0;
		int ans = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (map[i][j] == 1 && vis[i][j] == 0) {
					if (calc(i, j, 0) > calc(i, j, 1))
						cover(i, j, 0);
					else
						cover(i, j, 1);
					++ans;
				}
		printf("%d\n", ans);
	}

	return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 50000 + 10;
const int MAXH = 1000 + 10;
const int MAXM = 12;
const int INF = 0x7FFFFFFF >> 3;

pair <int, int> f[MAXN][MAXM];
int n, H, D, P;

struct Monster {
    int type, h, d;
} mo[MAXN];

int bot[MAXH][MAXH][MAXM];

int dfs(int HP, int h, int d) {
    if (h <= 0)
	return 0;
    if (HP <= 0)
	return INF;
    if (bot[HP][h][d] != -1)
	return bot[HP][h][d];
    int &ret = bot[HP][h][d];
    ret = INF;
    ret = min(ret, dfs(HP - d, h - D, d));
    ret = min(ret, dfs(min(HP + P, H) - d, h - D, d) + 1);
    if (HP > d) {
	ret = min(ret, dfs(min(HP - d + P, H), h - D, d) + 1);
    }
    return ret;
}

int main() {
    while (scanf("%d", &n) == 1) {
	for (int i = 1; i <= n; ++i) {
	    scanf("%d", &mo[i].type);
	    if (mo[i].type == 1)
		scanf("%d%d", &mo[i].h, &mo[i].d);
	}
	scanf("%d%d%d", &H, &D, &P);
	memset(bot, -1, sizeof(bot));
	for (int i = 0; i <= n; ++i)
	    for (int j = 0; j <= 5; ++j)
		f[i][j] = make_pair(1, INF);
	f[0][0] = make_pair(0, 0);
	for (int i = 0; i < n; ++i)
	    for (int j = 0; j <= 5; ++j) {
		if (f[i][j].first > 0)
		    continue;
		if (mo[i + 1].type == 0) {
		    if (j < 5) {
			if (f[i][j] < f[i + 1][j + 1])
			    f[i + 1][j + 1] = f[i][j];
		    }
		    if (j == 5 && f[i][j] < f[i + 1][j])
			f[i + 1][j] = f[i][j];
		}
		else {
		    if (j == 5) {
			pair <int, int> tmp = make_pair(f[i][j].first - 1, f[i][j].second + dfs(H, mo[i + 1].h, mo[i + 1].d));
			if (tmp.second < INF && tmp < f[i + 1][0])
			    f[i + 1][0] = tmp;
		    }
		    if (f[i][j] < f[i + 1][j])
			f[i + 1][j] = f[i][j];
		}
	    }
	pair <int, int> ans = make_pair(1, INF);
	for (int i = 0; i <= 5; ++i)
	    if (f[n][i] < ans)
		ans = f[n][i];
	printf("%d %d\n", -ans.first, ans.second);
    }

    return 0;
}

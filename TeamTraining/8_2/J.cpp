#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0 ,1, 0, -1};
const int INF = 0x7FFFFFFF >> 2;

const int MAXN = 20 + 10;
const int MAXM = 5;

int dist[MAXN][MAXN][MAXM];
int tst_case, Tx, Ty;
int n, map[MAXN][MAXN];
int q[MAXN * MAXN * MAXM][3], head, tail;
bool vis[MAXN][MAXN][MAXM];

bool check(int x, int y) {
	if (x > 0 && x <= n && y > 0 && y <= n && map[x][y] == 0)
		return true;
	return false;
}

void BFS() {
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			for (int k = 0; k < 4; ++k) {
				dist[i][j][k] = INF;
				vis[i][j][k] = 0;
			}
	head = 0; tail = 1; q[head][0] = 1; q[head][1] = 1; q[head][2] = 0;
	dist[1][1][0] = 0;
	while (head != tail) {
		int px = q[head][0];
		int py = q[head][1];
		int k = q[head][2];
	        head++;
		int vx, vy, vk;
		vx = px + dx[k];
		vy = py + dy[k];
		vk = k;
		if (check(vx, vy) && !vis[vx][vy][vk]) {
			q[tail][0] = vx;
			q[tail][1] = vy;
			q[tail][2] = vk;
			tail++;
			vis[vx][vy][vk] = 1;
			dist[vx][vy][vk] = dist[px][py][k] + 1;
		}
		vx = px;
		vy = py;
		vk = (k + 1) % 4;
	        if (check(vx, vy) && !vis[vx][vy][vk]) {
			q[tail][0] = vx;
			q[tail][1] = vy;
			q[tail][2] = vk;
			tail++;
			vis[vx][vy][vk] = 1;
			dist[vx][vy][vk] = dist[px][py][k] + 1;
		}
		vx = px;
		vy = py;
		vk = (k + 3) % 4;
		if (check(vx, vy) && !vis[vx][vy][vk]) {
			q[tail][0] = vx;
			q[tail][1] = vy;
			q[tail][2] = vk;
			tail++;
			vis[vx][vy][vk] = 1;
			dist[vx][vy][vk] = dist[px][py][k] + 1;
		}
	}
}

int tmp[MAXM];

void BFS2() {
	for (int k = 0; k < 4; ++k)
		tmp[k] = dist[Tx][Ty][k];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			for (int k = 0; k < 4; ++k) {
				dist[i][j][k] = INF;
				vis[i][j][k] = 0;
			}
	tail = 0;
	for (int k = 0; k < 4; ++k) {
		q[tail][0] = Tx; q[tail][1] = Ty; q[tail][2] = k;
		dist[Tx][Ty][k] = tmp[k];
		vis[Tx][Ty][k] = 1;
		tail++;
	}
	head = 0;
	while (head != tail) {
		int px = q[head][0];
		int py = q[head][1];
		int k = q[head][2];
	        head++;
		int vx, vy, vk;
		vx = px + dx[k];
		vy = py + dy[k];
		vk = k;
		if (check(vx, vy) && !vis[vx][vy][vk]) {
			q[tail][0] = vx;
			q[tail][1] = vy;
			q[tail][2] = vk;
			tail++;
			vis[vx][vy][vk] = 1;
			dist[vx][vy][vk] = dist[px][py][k] + 1;
		}
		vx = px;
		vy = py;
		vk = (k + 1) % 4;
	        if (check(vx, vy) && !vis[vx][vy][vk]) {
			q[tail][0] = vx;
			q[tail][1] = vy;
			q[tail][2] = vk;
			tail++;
			vis[vx][vy][vk] = 1;
			dist[vx][vy][vk] = dist[px][py][k] + 1;
		}
		vx = px;
		vy = py;
		vk = (k + 3) % 4;
		if (check(vx, vy) && !vis[vx][vy][vk]) {
			q[tail][0] = vx;
			q[tail][1] = vy;
			q[tail][2] = vk;
			tail++;
			vis[vx][vy][vk] = 1;
			dist[vx][vy][vk] = dist[px][py][k] + 1;
		}
	}
}

int main() {
	scanf("%d", &tst_case);
	while (tst_case--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				map[i][j] = 0;
		for (;;) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			if (a == -1 && b == -1 && c == -1)
				break;
			++b; ++c;
			if (a == 1 || a == 2)
				map[b][c] = 1;
			if (a == 3)
				Tx = b, Ty = c;
		}
		BFS();
		BFS2();
		int ans = INF;
		for (int i = 0; i < 4; ++i)
			ans = min(ans, dist[1][1][i] + 2);
		if (ans >= 100)
			puts("-1");
		else
			printf("%d\n", 1000 - ans * 10);
	}

	return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 70000 + 10;

int dist[MAXN], n, path[MAXN], num[MAXN];
int q[MAXN], head, tail, ans[MAXN * 100], tt[MAXN * 100];
int x, y;
bool vis[MAXN];

void BFS1() {
	head = 0; tail = 1;
	for (int i = 0; i < n; ++i)
		vis[i] = 0;
	dist[x % n] = 1;
	vis[x % n] = 1;
	q[head] = x % n;
	while (head < tail) {
		int p = q[head++];
		int tmp = (p * 10 + x) % n;
		if (!vis[tmp]) {
			vis[tmp] = 1;
			q[tail++] = tmp;
			dist[tmp] = dist[p] + 1;
		}
	}
}

void BFS2() {
	head = 0; tail = 0;
	for (int i = 0; i < n; ++i)
		vis[i] = 0;
	for (int i = 0; i < n; ++i)
		path[i] = num[i] = 0;
	if (x != 0) {
		q[tail++] = x % n;
		dist[x % n] = 1;
		vis[x % n] = 1;
		num[x % n] = 1;
		path[x % n] = -1;
	}
	q[tail++] = y % n;
	dist[y % n] = 1;
	vis[y % n] = 1;
	num[y % n] = 2;
	path[y % n] = -1;
	while (head < tail) {
		int p = q[head++];
		int tmp = (p * 10 + x) % n;
		if (!vis[tmp]) {
			vis[tmp] = 1;
			q[tail++] = tmp;
			dist[tmp] = dist[p] + 1;
			path[tmp] = p;
			num[tmp] = 1;
		}
		tmp = (p * 10 + y) % n;
		if (!vis[tmp]) {
			vis[tmp] = 1;
			q[tail++] = tmp;
			dist[tmp] = dist[p] + 1;
			path[tmp] = p;
			num[tmp] = 2;
		}
	}
}

int main() {
	while (scanf("%d", &n) == 1) {
		if (n == 0)
			break;
		if (n < 10) {
			printf("%d\n", n);
			continue;
		}
		int ans1 = 0, ans2 = 100000000, ansx;
		for (x = 1; x <= 9; ++x) {
			BFS1();
			if (vis[0] && dist[0] < ans2) {
				ans2 = dist[0];
				ans1 = 1;
				ansx = x;
			}
		}
		if (ans1) {
			for (int i = 1; i <= ans2; ++i)
				printf("%d", ansx);
			puts("");
			continue;
		}
		for (x = 0; x <= 9; ++x)
			for (y = x + 1; y <= 9; ++y) {
				BFS2();
				if (vis[0]){
					if (dist[0] < ans2) {
						ans2 = dist[0];
						int cur = 0, len = 0;
						while (cur != -1) {
							if (num[cur] == 1)
								ans[++len] = x;
							else
								ans[++len] = y;
							cur = path[cur];
						}
					}
					else if (dist[0] == ans2) {
						int cur = 0, len = 0;
						while (cur != -1) {
							if (num[cur] == 1)
								tt[++len] = x;
							else
								tt[++len] = y;
							cur = path[cur];
						}
						bool flag = true;
						for (int i = ans2; i; --i) {
							if (ans[i] < tt[i]) {
								break;
							}
							else if (ans[i] > tt[i]) {
								flag = false;
								break;
							}
						}
						if (!flag) {
							for (int i = 1; i <= ans2; ++i)
								ans[i] = tt[i];
						}
					}
				}
			}
		for (int i = ans2; i; --i)
			printf("%d", ans[i]);
		puts("");
	}

	return 0;
}

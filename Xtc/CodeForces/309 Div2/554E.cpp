#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int Maxn = 100000 + 100, Maxm = 2 * (100000 + 100);
const int Mod = 1000000007;

class Graph {
public:
	int head[Maxn], Next[Maxm], No[Maxm], tot, w[Maxm];
	void init() {
		tot = 1;
		memset(head, 0, sizeof head);
	}
	void add(int x, int y, int ty) {
		Next[tot] = head[x];
		head[x] = tot;
		No[tot] = y;
		w[tot++] = ty;
	}
}G;

int cnt = 0;
bool vis[Maxn];
int color[Maxn];

bool dfs(int x, int ty) {
	if(color[x] != -1 && color[x] != ty)
		return false;
	if(color[x] != -1)
		return true;
	color[x] = ty;
	vis[x] = true;
	for(int i = G.head[x]; i; i = G.Next[i]) {
		int y = G.No[i];
		if(G.w[i]) {
			if(!dfs(y, ty))
				return false;
		}
		else {
			if(!dfs(y, !ty))
				return false;
		}
	}
	return true;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	G.init();
	for(int i = 0; i < m; ++i) {
		int x, y, ty;
		scanf("%d%d%d", &x, &y, &ty);
		G.add(x, y, ty);
		G.add(y, x, ty);
	}
	memset(vis, false, sizeof vis);
	memset(color, -1, sizeof color);
	long long ans = 1;
	bool isFirst = true;
	for(int i = 1; i <= n; ++i) {
		if(!vis[i]) {
			if(!isFirst)
				ans = ans * 2 % Mod;
			else
				isFirst = false;
			if(!dfs(i, 0))
				ans = 0;
		}
	}
	cout << ans << endl;
	return 0;
}
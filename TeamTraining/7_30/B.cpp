#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

const int MAXN = 400 + 10;
const double eps = 1e-8;

int n;
double x[MAXN], y[MAXN], z[MAXN];
vector <int> G[MAXN];

double sqr(double x) {
	return x * x;
}

double dist(int i, int j) {
	return sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]) + sqr(z[i] - z[j]));
}

int ID(int x, int y) {
	return (x - 1) * 2 + y - 1;
}

void AddEdge(int a, int b) {
	G[a].push_back(b);
	G[b].push_back(a);
}

bool vis[MAXN];
int stk[MAXN], Top;

bool dfs(int p) {
	if (vis[p ^ 1])
		return false;
	if (vis[p])
		return true;
	vis[p] = true;
	stk[++Top] = p;
	for (int i = 0; i < (int)G[p].size(); ++i) {
		int v = G[p][i];
		if (!dfs(v))
			return false;
	}
	return true;
}

bool check_out(int idx) {
	return (x[idx] >= 0 && x[idx] <= 10000 && y[idx] >= 0 && y[idx] <= 10000 && z[idx] >= 0 && z[idx] <= 10000);
}

bool check(double x) {
	for (int i = 0; i <= ID(n, 2); ++i)
		G[i].clear();
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) {
			if (dist(ID(i, 1), ID(j, 1)) < 2 * x + eps)
				AddEdge(ID(i, 1), ID(j, 2));
			if (dist(ID(i, 1), ID(j, 2)) < 2 * x + eps)
				AddEdge(ID(i, 1), ID(j, 1));
			if (dist(ID(i, 2), ID(j, 1)) < 2 * x + eps)
				AddEdge(ID(i, 2), ID(j, 2));
			if (dist(ID(i, 2), ID(j, 2)) < 2 * x + eps)
				AddEdge(ID(i, 2), ID(j, 1));
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= 2; ++j)
			if (!check_out(ID(i, j))) {
				for (int k = 1; k <= n; ++k) {
					if (i != k) {
						AddEdge(ID(k, 1), ID(i, 3 - j));
						AddEdge(ID(k, 2), ID(i, 3 - j));
					}
				}
			}
	for (int i = 0; i <= ID(n, 2); ++i)
		vis[i] = 0;
	for (int i = 1; i <= n; ++i)
		if (!vis[ID(i, 1)] && !vis[ID(i, 2)]) {
			Top = 0;
			if (!dfs(ID(i, 1))) {
				for (int j = 1; j <= Top; ++j)
					vis[stk[j]] = false;
				Top = 0;
				if (!dfs(ID(i, 2)))
					return false;
			}
		}
	return true;
}

void Solve() {
	double L = 0, R = 1e18;
	while (R - L > eps) {
		double mid = (L + R) / 2;
		if (check(mid))
			L = mid;
		else
			R = mid;
	}
	L *= 1000.0;
	L = floor(L);
	L /= 1000.0;
	cout << setiosflags(ios::fixed) << setprecision(3) << L << endl;
}

int main() {
	ios::sync_with_stdio(false);
	while (cin >> n) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= 2; ++j)
				cin >> x[ID(i, j)] >> y[ID(i, j)] >> z[ID(i, j)];
		}
		Solve();
	}

	return 0;
}

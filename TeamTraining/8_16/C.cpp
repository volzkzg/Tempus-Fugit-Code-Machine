#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 0x7FFFFFFF/2;
const int N = 1010, K = 12, E = 55;
int f[N][K][E][5], n, k, e;
const int consume[4] = {0, 1, 2, 3};
const int power[4] = {0, 4, 8, 11};
int a[N];

inline void update(int &x, int y)
{
	x = min(x, y);
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		static int tst_cas = 0;
		cout << "Case #" << ++tst_cas << ": ";
		cin >> n >> k >> e;
		for (int x = 0; x <= n + 1; ++x)
			for (int y = 0; y <= k; ++y)
				for (int z = 0; z <= e; ++z)
					for (int col = 0; col <= 3; ++col)
						f[x][y][z][col] = INF;

		for (int i = 1; i <= n; ++i)
			cin >> a[i];
		f[0][0][e][0] = 0;
		for (int x = 0; x < n; ++x)
			for (int y = 0; y <= k; ++y)
				for (int z = 0; z <= e; ++z)
					for (int col = 0; col <= 3; ++col) {
						if (f[x][y][z][col] == INF) continue;
						for (int next_col = 0; next_col <= 3; ++next_col) {
							if (col == next_col) {
								//if (z - consume[next_col] < 0) break; /// to do checking
								if (z - consume[next_col] < 0) {
									update(f[x + 1][k][0][0],
									       f[x][y][z][col] + a[x + 1]);
								} else {
									update(f[x + 1][y][z - consume[next_col]][next_col],
									       f[x][y][z][col] + max(0, (a[x + 1] - power[next_col])));
								}
							} else {
								if (z - consume[next_col] < 0) {
									update(f[x + 1][k][0][0],
									       f[x][y][z][col] + a[x + 1]);
								} else {
									if (y >= k) continue;
									update(f[x + 1][y + 1][z - consume[next_col]][next_col],
									       f[x][y][z][col] + max(0, (a[x + 1] - power[next_col])));
								}
							}
						}
					}
		int ans = INF;
		for (int y = 0; y <= k; ++y)
			for (int z = 0; z <= e; ++z)
				for (int col = 0; col <= 3; ++col) {
					ans = min(ans, f[n][y][z][col]);
				}

		cout << ans << endl;
	}
	return 0;
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 111;
const int M = 111;
int n, m, c[N], L[N], R[N], f[N][N];

inline void update(int &x, int y)
{
	if (x == -1)
		x = y;
	else
		x = min(x, y);
}

void calc(int x, int y)
{
	if (y < x) {
		f[x][y] = 0;
		return;
	}
	if (x == y) {
		f[x][y] = 1;
		return;
	}
	if (f[x][y] != -1)
		return;
	calc(x + 1, y);
	update(f[x][y], f[x + 1][y] + 1);
	for (int i = x + 1; i <= y; ++i) {
		if (c[x] == c[i]) {
			calc(x + 1, i - 1);
			calc(i, y);
			update(f[x][y], f[x + 1][i - 1] + f[i][y]);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		static int tst = 0;
		cout << "Case " << ++tst << ": ";
		cin >> n >> m;
		for (int i = 1; i <= n; ++i)
			cin >> c[i];
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				f[i][j] = -1;
		calc(1, n);
		//cout << 1 << " " << n << " " << f[1][n] << endl;
		cout << f[1][n] << endl;
	}
	return 0;
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 55;
const long long MOD = 1000000007;
long long C[N][N], num[N], f[N][N], B[N][N];
int T, n, m;

bool check(int x, int y)
{
	static vector<int> u;
	static vector<int> v;
	u.clear(), v.clear();
	int tmp;
	tmp = num[x];
	while (tmp) {
		u.push_back(tmp % 10);
		tmp /= 10;
	}
	tmp = num[y];
	while (tmp) {
		v.push_back(tmp % 10);
		tmp /= 10;
	}

	long long mi = 1, suffix, prefix;
	int len = min((int)u.size(), (int)v.size());
	reverse(v.begin(), v.end());
	suffix = prefix = 0;
	for (int i = 1; i <= len; ++i) {
		suffix = suffix + u[i - 1] * mi;
		mi *= 10;
		prefix = prefix * 10 + v[i - 1];
		if (suffix == prefix && i >= 2) {
			return true;
		}
	}
	return false;
}

void multiply(long long u[][N], long long v[][N])
{
	static long long ret[N][N];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			ret[i][j] = 0;
			for (int k = 1; k <= n; ++k)
				ret[i][j] = (ret[i][j] + u[i][k] * v[k][j]) % MOD;
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			u[i][j] = ret[i][j];
}

int main()
{
	ios::sync_with_stdio(false);

	cin >> T;
	while (T--) {
		cin >> n >> m;
		assert(n >= 0);
		assert(m >= 0);
		for (int i = 1; i <= n; ++i) {
			cin >> num[i];
		}
		sort(num + 1, num + 1 + n);
		n = unique(num + 1, num + 1 + n) - num -1;
		if (m == 0) {
			cout << 0 << endl;
			continue;
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				C[i][j] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (check(i, j)) C[i][j] = 1;
				//cout << C[i][j] << " ";
			}
			//cout<< endl;
		}
		m--;


		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				f[i][j] = 0;
		for (int i = 1; i <= n; ++i)
			f[i][i] = 1;
		while (m) {
			if (m & 1)
				multiply(f, C);
			m >>= 1;
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					B[i][j] = C[i][j];
			multiply(C, B);
		}
		long long ans = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) {
				ans = (ans + f[i][j]) % MOD;
			}
		cout << ans << endl;
	}
	return 0;
}

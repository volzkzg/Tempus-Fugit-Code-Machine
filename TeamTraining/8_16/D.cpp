#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 555;
const long long MOD = 1000000007;
long long C[N][N], jie[N], g[N][N], G[N][N], f[N][N];

long long getC(int x, int y)
{
	if (y > x) return 0;
	if (x < 0 || y < 0) return 0;
	return C[x][y];
}

long long getA(int x, int y)
{
	if (y > x) return 0;
	if (x < 0 || y < 0) return 0;
	return C[x][y] * jie[y] % MOD;
}

void init()
{
	jie[0] = 1;
	for (int i = 1; i < N; ++i)
		jie[i] = jie[i - 1] * (long long)i % MOD;
	C[0][0] = 1;
	for (int i = 1; i < N; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
		}
	}
	int bound = 500;
	for (int i = 1; i <= bound; ++i)
	{
		for (int j = 1; j <= i; ++j)
			for (int k = 1; k <= j; ++k) {
				g[j][k] = getC(j - 2, k - 1) * jie[i - k - 1] % MOD;
				G[i][j] = (G[i][j] + g[j][k]) % MOD;
			}
	}
	for (int i = 1; i <= bound; ++i) {
		f[i][i] = 0;
		for (int j = i - 1; j >= 1; --j) {
			f[i][j] = (f[i][j + 1] + G[i][j + 1]) % MOD;
		}
	}
}

long long calc(int n, int k, int p)
{
	long long ret = getA(k - 1, n - p);
	ret = ret * getA(p - 1, k - 1 - (n - p)) % MOD;
	//ret = ret * jie[k - 1] % MOD;
	return ret;
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	init();
	cin >> T;
	while (T--) {
		static int tst_cas = 0;
		cout << "Case #" << ++tst_cas << ": ";
		int n, k, p;
		cin >> n >> k >> p;
		//if(k == n - 1)
		//{
			//cout << jie[n - 1] << endl;
			//continue;
		//}
		long long ans = 0;
		for (int t = 0; t < p; ++t) {
			//cout << n - k + 1 << " " << p - t << " " << f[n - k + 1][p - t] << endl;
			ans = (ans + f[n - k + 1][p - t] * getC(p - 1, t) % MOD * getC(n - p, k - t - 1) % MOD * jie[k - 1] % MOD) % MOD;
		}
		//cout << ans << endl;
		ans = (ans + calc(n, k, p)) % MOD;	
		cout << ans << endl;
	}
	return 0;
}

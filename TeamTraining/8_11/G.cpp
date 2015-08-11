#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 100000 + 10;
const long long MOD = 998244353;

long long QuickMod(long long a, long long b) {
	long long ret = 1;
	while (b) {
		if (b & 1)
			ret = ret * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ret;
}

long long f[MAXN], fac[MAXN];
int n;
long long sum0, sum1, sum2;

int main() {
	ios::sync_with_stdio(false);
	f[1] = 1;
	fac[0] = 1;
	for (int i = 1; i < MAXN; ++i)
		fac[i] = fac[i - 1] * (long long)i % MOD;
	sum1 = sum2 = 1;
	sum0 = 2;
	for (int i = 2; i < MAXN; ++i) {
		f[i] = sum0 * (long long)i % MOD - 2 * sum1 % MOD + sum2 * QuickMod((long long)i, MOD - 2) % MOD;
		f[i] = (f[i] % MOD + MOD) % MOD;
		sum0 = (sum0 + f[i]) % MOD;
		sum1 = (sum1 + f[i] * (long long)i) % MOD;
		sum2 = (sum2 + f[i] * (long long)i % MOD * (long long)i) % MOD;
	}
	int n;
	while (cin >> n) {
		cout << fac[n] * f[n] % MOD << endl;
	}

	return 0;
}

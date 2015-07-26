#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const long long K = 2000000000;
long long f[50];
int len, n;

long long calc(long long k)
{
	long long ret = 0;
	while (k) {
		int pos = upper_bound(f + 1, f + len + 1, k) - f - 1;
		//if (k == 4) cout << f[pos] << " " << k << endl;
		k -= f[pos];
		ret ++;
	}
	return ret;
}

int main()
{
	ios::sync_with_stdio(false);
	f[1] = 1;
	f[2] = 2;
	for (len = 3; f[len - 1] < K; len ++)
		f[len] = f[len - 1] + f[len - 2];
	len--;
	int T;
	cin >> T;
	while (T--) {
		static int tst = 0;
		cout << "Case " << ++tst << ": ";
		long long ans = 1;
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			long long k;
			cin >> k;
			ans *= calc(k);
		}
		cout << ans << endl;
	}
	return 0;
}

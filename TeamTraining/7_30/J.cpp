#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int Mod = 1000000007;
const int Maxn = 200000;
long long pow2[Maxn];

long long f[Maxn];
long long preSum[Maxn];

long long getpreSum(int r, int l)
{
	if(l < 0) l = 0;
	if(l == 0)
		return preSum[r];
	else
	{
		long long ret = preSum[r] - preSum[l - 1];
		ret %= Mod;
		ret += Mod;
		ret %= Mod;
		return ret;
	}
}

int main()
{
	pow2[0] = 1;
	for(int i = 1; i < Maxn; ++i)
		pow2[i] = pow2[i - 1] * 2 % Mod;
	int n, m;
	while(scanf("%d%d", &n, &m) == 2)
	{
		long long ans = 0;
		f[0] = 1;
		preSum[0] = 1;
		for(int i = 1; i <= n; ++i)
		{
			f[i] = getpreSum(i - 1, i - m);
			if(i < m)
				f[i]++;
			preSum[i] = (preSum[i - 1] + f[i]) % Mod;
		//	cout << i << " " << f[i] << endl;
		}
		ans = pow2[n] - f[n];
		ans %= Mod;
		if(ans < 0) ans += Mod;
		cout << ans << endl;
	}
	return 0;
}

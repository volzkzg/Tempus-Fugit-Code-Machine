#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int Mod = 1000000007;

long long f[20], g[20];
long long ans = 0;
int C;

pair<int, int> fac[20];

long long seq[20], res[20];

void calc(int msk)
{
	long long pCnt = 1, qCnt = 1;
	long long curPSum = 1;
	for(int i = 0; i < C; ++i)
	{
		if((msk >> i) & 1)
		{
			long long tmp = res[i];
			f[i] = (i - 1 >= 0 ? f[i - 1] : 1) * tmp % Mod;
		}
		else
		{
			pCnt = (pCnt * fac[i].second) % Mod;
			long long pre = (i - 1 >= 0 ? f[i - 1] : 1);
		/*	for(int j = 0; j < fac[i].second; ++j)
			{
				f[i] = (f[i] + pre * tmp) % Mod;
				tmp = tmp * fac[i].first % Mod;
			}*/
			f[i] = (pre * seq[i]) % Mod;
		}
	}
	int qmsk = ((1 << C) - 1) ^ msk;
	for(int i = 0; i < C; ++i)
	{
		if((qmsk >> i) & 1)
		{
			long long tmp = res[i];
			g[i] = (i - 1 >= 0 ? g[i - 1] : 1) * tmp % Mod;
		}
		else
		{
			qCnt = (qCnt * (fac[i].second + 1)) % Mod;
			long long pre = (i - 1 >= 0 ? g[i - 1] : 1);
			g[i] = (pre * ((seq[i] + res[i]) % Mod)) % Mod;
		}
	}
	ans = (ans + (pCnt * g[C - 1] % Mod + qCnt * f[C - 1] % Mod) % Mod) % Mod;
}

int main()
{
	int T;
	scanf("%d", &T);
	for(int iCase = 1; iCase <= T; ++iCase)
	{
		printf("Case %d: ", iCase);
		scanf("%d", &C);
		for(int i = 0; i < C; ++i)
			scanf("%d%d", &fac[i].first, &fac[i].second);
		ans = 0;
		for(int i = 0; i < C; ++i)
		{
			seq[i] = 0;
			long long tmp = 1;
			for(int j = 0; j < fac[i].second; ++j)
			{
				seq[i] = (seq[i] + tmp) % Mod;
				tmp = tmp * fac[i].first % Mod;
			}
			res[i] = tmp;
		}
		for(int i = 0; i < (1 << C); ++i)
		{
			calc(i);
		}
		long long n = 1;
		for(int i = 0; i < C; ++i)
			n = n * res[i] % Mod;
		ans += 2 * n;
		ans %= Mod;
		ans = ans * 500000004LL % Mod;
		printf("%d\n", (int)ans);
	}
	return 0;
}

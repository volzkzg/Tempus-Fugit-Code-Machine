#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int Maxn = 1000000;
const int MaxNum = 11000;

int a[Maxn], L[Maxn], R[Maxn];
int c[MaxNum];

vector<int> factor[MaxNum];

int main()
{
	for(int i = 1; i < MaxNum; ++i)
	{
		for(int j = 1; j * j <= i; ++j)
		{
			if(i % j == 0)
			{
				factor[i].push_back(j);
				factor[i].push_back(i / j);
			}
		}
	}
	int n;
	while(scanf("%d", &n) == 1)
	{
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i), L[i] = 0, R[i] = n + 1;
		for(int i = 0; i < MaxNum; ++i)
			c[i] = -1;
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 0; j < factor[a[i]].size(); ++j)
				L[i] = max(L[i], c[factor[a[i]][j]]);
			c[a[i]] = i;
		}
		for(int i = 0; i < MaxNum; ++i)
			c[i] = n + 2;
		for(int i = n; i >= 1; --i)
		{
			for(int j = 0; j < factor[a[i]].size(); ++j)
				R[i] = min(R[i], c[factor[a[i]][j]]);
			c[a[i]] = i;
		}
		long long ans = 0;
		const int Mod = 1000000007;
		for(int i = 1; i <= n; ++i)
		{
			long long delta = 0;
			long long l = L[i], r = R[i];
			ans += (i - l) * (r - i);
			ans %= Mod;
		}
		printf("%d\n", (int)ans);
	}
	return 0;
}

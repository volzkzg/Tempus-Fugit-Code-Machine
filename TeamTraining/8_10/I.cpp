#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int Maxn = 1600;

long double f[2][Maxn][Maxn]; //g[2][Maxn][Maxn]; // count sum smallest

int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	memset(f, 0, sizeof f);
	//memset(g, 0, sizeof g);
	for(int i = 1; i <= n; ++i)
		f[1][i][i] = 1;
	for(int i = n; i >= 1; --i)
	{
		for(int j = i - 1; j >= 1; --j)
			f[1][i][j] = 1;
	}
	for(int count = 2; count <= k; ++count)
	{
		int cur = (count & 1);
		int pre = cur ^ 1;
		for(int sum = 1; sum <= n; ++sum)
			for(int smallest = 1; (smallest - 1) * count <= sum; ++smallest)
				f[cur][sum][smallest] = 0;//g[cur][sum][smallest] = 0;
		
		for(int sum = 1; sum <= n; ++sum)
		{
			for(int smallest = 1; smallest * count <= sum; ++smallest)
			{
				f[cur][sum][smallest] = f[pre][sum - smallest][smallest];
			//	printf("f[%d][%d][%d] = %lld\n", count, sum, smallest, f[cur][sum][smallest]);
			}
			if(count != k)
			{
				for(int smallest = (sum / count); smallest >= 1; --smallest)
				{
					f[cur][sum][smallest] += f[cur][sum][smallest + 1];
				}
			}
		}
	}
	long double ans = 0;
	for(int small = 1; small * k <= n; ++small)
		ans += f[k & 1][n][small];
	cout << ans << endl;
	return 0;
}

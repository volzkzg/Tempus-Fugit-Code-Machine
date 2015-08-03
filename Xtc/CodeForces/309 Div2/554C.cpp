#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int Mod = 1000000007;

long long f[1001][1001];
long long preSum[1001][1001];

int cnt[1100];
long long C[1100][1100];

int main()
{
	for(int i = 0; i < 1100; ++i)
	{
		C[i][i] = C[i][0] = 1;
		for(int j = 1; j < i; ++j)
		{
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
			C[i][j] %= Mod;
		}
	}
	int k;
	scanf("%d", &k);
	int sum = 0;
	for(int i = 0; i < k; ++i)
		scanf("%d", cnt + i), sum += cnt[i];
	int pSum = 0;
	for(int i = 0; i < k; ++i)
	{
		for(int j = 0; j < sum; ++j)
		{
			if(i == 0)
				f[i][j] = C[j][cnt[0] - 1];
			else
			{
				if(j == 0)
				{
					if(j >= pSum)
						f[i][j] = C[j - pSum][cnt[i] - 1];
					else
						f[i][j] = 0;
				}
				else
				{
					if(j - pSum < 0)
						f[i][j] = 0;
					else
						f[i][j] = preSum[i - 1][j - 1] * C[j - pSum][cnt[i] - 1] % Mod;
				}
			}
		}
		preSum[i][0] = f[i][0];
		for(int j = 1; j < sum; ++j)
			preSum[i][j] = (preSum[i][j - 1] + f[i][j]) % Mod;
		pSum += cnt[i];
	}
	cout << f[k - 1][sum - 1] % Mod << endl;
	return 0;
}
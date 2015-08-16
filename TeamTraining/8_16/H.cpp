#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int Maxn = 2100;

int f[Maxn][Maxn];
int preSum[Maxn][Maxn];
char s[Maxn];
int n, m, k;

int main()
{
	int T;
	scanf("%d", &T);
	for(int iCase = 1; iCase <= T; ++iCase)
	{
		scanf("%d%d%d", &n, &m, &k);
		scanf("%s", s + 1);
		for(int i = 0; i <= m; ++i)
		{
			f[2 * n][i] = (i != 0 && i <= k);
			if(i != 0)
				preSum[2 * n][i] = preSum[2 * n][i] + f[2 * n][i];
			else
				preSum[2 * n][i] = f[2 * n][i];
		}
		for(int i = 2 * n - 1; i >= 1; --i)
		{
			for(int j = 0; j <= m; ++j)
			{
				if(j == 0)
					f[i][j] = 0;
				else if(j <= k)
				{
					f[i][j] = 1;
				}
				else
				{
					int v = preSum[i + 1][j - 1];
					if(j - k - 1 >= 0)
						v -= preSum[i + 1][j - k - 1];
					int len = min(j, k);
					if(s[i + 1] == s[i])
						f[i][j] = (v > 0);
					else
						f[i][j] = (len - v) > 0;
				}
				if(j == 0)
					preSum[i][j] = 0;
				else
					preSum[i][j] = preSum[i][j - 1] + f[i][j];
			}
		}
		printf("Case #%d: ", iCase);
		if(s[1] == 'A')
		{
			if(f[1][m] == 1)
				putchar('A');
			else
				putchar('B');
		}
		else
		{
			if(f[1][m] == 1)
				putchar('B');
			else
				putchar('A');
		}
		puts("");
	}
	return 0;
}

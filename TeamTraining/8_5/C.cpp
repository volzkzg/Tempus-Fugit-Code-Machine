#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

const int Maxn = 1100;

long double f[Maxn], g[Maxn];
long double fact[Maxn];

long long mypow[Maxn][Maxn];

long double C(int n, int m)
{
	return fact[n] / fact[m] / fact[n - m];
}

long double A(int n, int m)
{
	return fact[n] / fact[n - m];
}

int main()
{
	fact[0] = 1;
	for(int i = 1; i < Maxn; ++i)
		fact[i] = fact[i - 1] * i;
	cout << fact[1000] << endl;
	for(int i = 1; i < Maxn; ++i)
	{
		mypow[i][0] = 1;
		for(int j = 1; j < Maxn; ++j)
			mypow[i][j] = mypow[i][j - 1] * i;
	}
	int n, m;
	while(scanf("%d%d", &n, &m) == 2)
	{
		if(m >= n)
		{
			printf("%.9f\n", 1.0);
			continue;
		}
		else
		{
			for(int i = 0; i <= n; ++i)
				f[i] = 0;
			f[0] = 1;
			for(int j = 1; j <= m; ++j)
			{
				for(int i = 0; i <= n; ++i)
					g[i] = 0;
				for(int i = n; i >= 0; --i)
				{
					for(int t = 0; t * j + i <= n; ++t)
					{
						long double delta = A(n - i, t * j) / fact[t] / mypow[j][t];
						g[i + t * j] += f[i] * delta;
					}
				}
				for(int i = 0; i <= n; ++i)
				{
					f[i] = g[i];
					cout << f[i] << " ";
					//printf("%.9f ", (double)f[i]);
				}
				puts("");
			}
		}
		cout << setiosflags(ios::fixed) << setprecision(10) << f[n] / fact[n] << endl;
		//printf("%.9f\n", (double)(f[n] / fact[n]));
	}
	return 0;
}

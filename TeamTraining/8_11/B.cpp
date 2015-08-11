#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int pairs[12][2] = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {2, 4}, {2, 6}, {4, 6}, {3, 6}};

const int Maxn = 1100000;

int b[Maxn], p[Maxn], tot;

int f[Maxn];
int Count[8][Maxn];

int calc(int x)
{
	int ret = 0;
	while(x != 1)
	{
		ret++;
		int p = b[x];
		while(x % p == 0) x /= p;
	}
	return ret;
}

void prepare()
{
	tot = 0;
	memset(b, 0, sizeof b);
	for(int i = 2; i < Maxn; ++i)
	{
		if(!b[i]) b[i] = i, p[tot++] = i;
		for(int j = 0; j < tot && 1LL * p[j] * i < Maxn; ++j)
		{
			b[i * p[j]] = p[j];
			if(i % p[j] == 0)
				break;
		}
	}
	for(int i = 2; i < Maxn; ++i)
	{
		f[i] = calc(i);
	}
}

int gcd(int a, int b)
{
	if(a == 0) return b;
	return gcd(b % a, a);
}

int main()
{
	prepare();
	memset(Count, 0, sizeof Count);
	for(int i = 2; i < Maxn; ++i)
		Count[f[i]][i] = 1;
	for(int c = 1; c <= 7; ++c)
	{
		for(int i = 2; i < Maxn; ++i)
			Count[c][i] += Count[c][i - 1];
	}
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int L, R;
		scanf("%d%d", &L, &R);
		int ans = 1;
		for(int i = 0; i < 10; ++i)
		{
			int p = pairs[i][0];
			int q = pairs[i][1];
			if(p == q)
			{
				if(Count[p][R] - Count[p][L - 1] >= 2)
					ans = max(ans, p);
			}
			else
			{
				if(Count[p][R] - Count[p][L - 1] >= 1 && Count[q][R] - Count[q][L - 1] >= 1)
					ans = max(ans, gcd(p, q));
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

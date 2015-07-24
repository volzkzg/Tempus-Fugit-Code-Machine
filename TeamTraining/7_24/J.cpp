#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int Maxn = 1100;

char s[Maxn][600];
int len[Maxn];

const int p = 131;

unsigned long long hash[Maxn];
unsigned long long rhash[Maxn];
unsigned long long pow[Maxn * 2];

void getHash(int pos, unsigned long long &h)
{
	h = 0;
	for(int i = 0; i < len[pos]; ++i)
		h = h + s[pos][i] * pow[i];
}

int check(int a, int b)
{
	long long h1, h2;
	h1 = h2 = 0;
	h1 = hash[a] + hash[b] * pow[len[a]];
	h2 = rhash[b] + rhash[a] * pow[len[b]];
	return h1 == h2;
}

int main()
{
	pow[0] = 1;
	for(int i = 1; i < Maxn * 2; ++i)
		pow[i] = pow[i - 1] * p;
	int T;
	scanf("%d", &T);
	for(int cas = 1; cas <= T; ++cas)
	{
		printf("Case #%d: ", cas);
		int n;
		scanf("%d", &n);
	
		for(int i = 1; i <= n; ++i)
		{
			scanf("%s", s[i]);
			len[i] = strlen(s[i]);
			getHash(i, hash[i]);
			reverse(s[i], s[i] + len[i]);
			getHash(i, rhash[i]);
		}
	
		int ans = 0;
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= n; ++j)
			{
				if(i == j) continue;
				if(check(i, j))
				{
					ans++;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int Mod = 105225319;

long long fastmul(long long a, long long b)
{
	long long ret = 1;
	while(b)
	{
		if(b & 1) ret = ret * a % Mod;
		a = a * a % Mod, b >>= 1;
	}
	return ret;
}

long long inv(long long x)
{
	return fastmul(x, Mod - 2);
}

long long com[2000][2000];

void prepare()
{
	for(int i = 0; i < 2000; ++i)
		com[i][0] = com[i][i] = 1;
	for(int i = 1; i < 2000; ++i)
		for(int j = 1; j < i; ++j)
		{
			com[i][j] = (com[i - 1][j - 1] + com[i - 1][j]) % Mod;
		}
}

long long p[2000 * 2000];

int main()
{
	int T;
	scanf("%d", &T);
	prepare();
	for(int iCase = 1; iCase <= T; ++iCase)
	{
		printf("Case #%d: ", iCase);
		int n, m;
		scanf("%d%d", &n, &m);
		p[0] = 1;
		for(int i = 1; i < n * n; ++i)
			p[i] = p[i - 1] * m % Mod;
		long long ans = 0;
		for(int A = 1; A <= n; ++A)
		{
			for(int C = 0; C <= A; ++C)
			{
				int B = n - A + C;
				if(B == 0) continue;
				long long delta = com[n][A] * com[A][C] % Mod;
				delta = delta * inv(2) % Mod;
				int edges = A * (A - 1) / 2 + B * (B - 1) / 2 - C * (C - 1) / 2;
				delta = delta * p[(n) * (n - 1) / 2 - edges] % Mod;
				ans = (ans + delta) % Mod;
			}
		}
		printf("%d\n", (int)(ans % Mod));
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int Maxn = 110000;

long long f[Maxn][110], g[Maxn][110];
int n, w[Maxn], q[Maxn], fa[Maxn];

vector<int> nxt[Maxn], ch[Maxn];

void init()
{
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", w + i);
		nxt[i].clear(), ch[i].clear();
		fa[i] = -1;
		for(int j = 0; j <= 101; ++j)
			f[i][j] = g[i][j] = 0x3f3f3f3f;
	}
	for(int i = 0; i < n - 1; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		nxt[x].push_back(y);
		nxt[y].push_back(x);
	}
	int l, r; l = r = -1;
	q[++r] = 0;
	while(l < r)
	{
		int c = q[++l];
		for(int j = 0; j < nxt[c].size(); ++j)
		{
			int y = nxt[c][j];
			if(fa[c] == y) continue;
			q[++r] = y;
			fa[y] = c;
			ch[c].push_back(y);
		}
	}
}

void solve()
{
	for(int c = n - 1; c >= 0; --c)
	{
		int i = q[c];
		if(ch[i].size() == 0)
		{
			f[i][w[i]] = 1;
			g[i][0] = 0;
			continue;
		}
		//f
		static long long t[Maxn];
		long long sum = 0;
		for(int j = 0; j < ch[i].size(); ++j)
		{
			t[ch[i][j]] = min(f[ch[i][j]][1], f[ch[i][j]][0]);
			sum += t[ch[i][j]];
			sum = min(sum, (long long)0x3f3f3f3f);
		}
		for(int j = 0; j < ch[i].size(); ++j)
			f[i][0] = min(f[i][0], sum - t[ch[i][j]] + f[ch[i][j]][1]);
		if(w[i] == 0)
		{
			f[i][0] = min(f[i][0], sum + 1);
		}
		
		for(int j = 1; j <= 100; ++j)
		{
			sum = 0;
			for(int k = 0; k < ch[i].size(); ++k)
			{
				t[ch[i][k]] = min(t[ch[i][k]], f[ch[i][k]][j + 1]);
				t[ch[i][k]] = min(t[ch[i][k]], g[ch[i][k]][j - 1]);
				sum += t[ch[i][k]];
			}
			for(int k = 0; k < ch[i].size(); ++k)
			{
				f[i][j] = min(f[i][j], sum - t[ch[i][k]] + f[ch[i][k]][j + 1]);
			}
			if(j == w[i])
			{
				f[i][j] = min(f[i][j], sum + 1);
			}
		}
		//g
		sum = 0;
		for(int j = 0; j < ch[i].size(); ++j)
		{
			t[ch[i][j]] = f[ch[i][j]][0];
			sum += t[ch[i][j]];
		}
		g[i][0] = sum;
		for(int j = 1; j <= 100; ++j)
		{
			sum = 0;
			for(int k = 0; k < ch[i].size(); ++k)
			{
				t[ch[i][k]] = min(t[ch[i][k]], g[ch[i][k]][j - 1]);
				t[ch[i][k]] = min(t[ch[i][k]], f[ch[i][k]][j]);
				sum += t[ch[i][k]];
			}
			for(int k = 0; k < ch[i].size(); ++k)
			{
				g[i][j] = min(g[i][j], sum - t[ch[i][k]] + g[ch[i][k]][j - 1]);
			}
		}
	}
}

int main()
{
	while(scanf("%d", &n) == 1)
	{
		init();
		solve();
		long long ans = 0x3f3f3f3f;
		for(int j = 0; j <= 100; ++j)
			ans = min(ans, f[0][j]);
		printf("%d\n", (int)ans);
	}
	return 0;
}
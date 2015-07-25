#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <iostream>
#include <vector>
using namespace std;

const int Maxn = 30000;

class circle
{
public:
	int x, y, r;
	bool operator < (const circle &b) const
	{
		return r < b.r;
	}
};

circle c[Maxn];
vector<int> nxt[Maxn];

int n;

void init()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		nxt[i].clear();
		scanf("%d%d%d", &c[i].x, &c[i].y, &c[i].r);
	}
	nxt[n].clear();
	c[n].x = c[n].y = 0, c[n].r = 40000;
	n++;
}

long long dst(int a, int b)
{
	return 1LL * (c[a].x - c[b].x) * (c[a].x - c[b].x) + 1LL * (c[a].y - c[b].y) * (c[a].y - c[b].y);
}

void build()
{
	sort(c, c + n);
	for(int i = 0; i < n; ++i)
	{
		for(int j = i + 1; j < n; ++j)
		{
			if(dst(i, j) <= 1LL * (c[j].r - c[i].r) * (c[j].r - c[i].r))
			{
				nxt[j].push_back(i);
				break;
			}
		}
	}
}

int dfs(int x)
{
	int ret = 0;
	for(int i = 0; i < nxt[x].size(); ++i)
	{
		ret ^= (dfs(nxt[x][i]) + 1);
	}
	return ret;
}

void solve()
{
	printf("%s\n", dfs(n - 1) ? "Alice" : "Bob");
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		init();
		build();
		solve();
	}
	return 0;
}
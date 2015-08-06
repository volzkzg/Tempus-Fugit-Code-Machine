#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int Maxn = 1100;

int Link[Maxn], Match[Maxn];
bool vis[Maxn];
vector<int> nxt[Maxn];
int n, m;

bool find(int x)
{
	for (int i = 0; i < nxt[x].size(); ++i) 
	{
		int v = nxt[x][i];
		if(vis[v]) continue;
		vis[v] = 1;
		if (-1 == Link[v] || find(Link[v]))
		{
			Link[v] = x;
			Match[x] = v;
			return true;
		}
	}
	return false;
}

bool find2(int x)
{
	for(int i = 0; i < nxt[x].size(); ++i)
	{
		int v = nxt[x][i];
		if(vis[v]) continue;
		vis[v] = 1;
		if(-1 == Match[v] || find2(Match[v]))
			return true;
	}
	return false;
}

int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		memset(Link, -1, sizeof Link);
		memset(Match, -1, sizeof Match);
		for(int i = 0; i <= n + m; ++i)
			nxt[i].clear();
		for(int i = 0; i < n; ++i)
		{
			int cnt;
			scanf("%d", &cnt);
			for(int j = 0; j < cnt; ++j)
			{
				int y;
				scanf("%d", &y); y--;
				nxt[y].push_back(m + i);
			}
		}
		int cnt = 0;
		for(int i = 0; i < m; ++i)
		{
			memset(vis, 0, sizeof vis);
			if(find(i))
				cnt++;
		}
		bool flag = false;
		for(int i = 0; i < m; ++i)
		{
			if(Match[i] == -1 || find2(Match[i]))
			{
				flag = true;
				break;
			}
		}
		printf("%s\n", flag ? "Alice" : "Bob");
	}
	return 0;
}

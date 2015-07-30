#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>	

using namespace std;

const int Maxn = 10000;

bool vis[Maxn];

int main()
{
	memset(vis, false, sizeof vis);
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		vis[x] = vis[y] = true;
	}
	printf("%d\n", n - 1);
	for(int i = 1; i <= n; ++i)
	{
		if(!vis[i])
		{
			for(int j = 1; j <= n; ++j)
			{
				if(j == i) continue;
				printf("%d %d\n", i, j);
			}
			break;
		}
	}
	return 0;
}
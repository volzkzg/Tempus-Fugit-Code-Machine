#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int Maxn = 1100;

int n, m;

vector<int> nxt[Maxn];
int vis[Maxn];

int deg[Maxn];

int solve(int x)
{
	static int q[Maxn];
	int l, r;
	l = r = -1;
	q[++r] = x;
	while(l < r)
	{
		int cur = q[++l];
		vis[cur] = 1;
		for(int j = 0; j < nxt[cur].size(); ++j)
		{
			int y = nxt[cur][j];
			if(!vis[y])
			{
				vis[y] = 1;
				q[++r] = y;
			}
		}
	}
	int edgeCnt = 0;
	for(int i = 0; i <= r; ++i)
		edgeCnt += deg[q[i]];
	edgeCnt /= 2;
	int vCnt = r + 1;
	if(vCnt % 2 != 0 || edgeCnt != (vCnt / 2) * (vCnt / 2 - 1) + 1)
	{
		return 0;
	}
	int stdDeg = vCnt / 2 - 1;
	vector<int> vio;
	for(int i = 0; i <= r; ++i)
	{
		int y = q[i];
		if(deg[y] == stdDeg || deg[y] == stdDeg + 1)
		{
			if(deg[y] == stdDeg + 1)
				vio.push_back(y);
		}
		else
			return 0;
	}
	if(vio.size() != 2)
	{
		return 0;
	}
	int a, b;
	a = vio[0], b = vio[1];
	
	bool edgeExist = false;
	for(int i = 0; i < nxt[a].size(); ++i)
	{
		if(nxt[a][i] == b)
			edgeExist = true;
	}
	if(!edgeExist) return 0;
	
	l = r = -1;
	q[++r] = x;
	while(l < r)
	{
		int cur = q[++l];
		vis[cur] = 2;
		for(int j = 0; j < nxt[cur].size(); ++j)
		{
			int y = nxt[cur][j];
			if(cur == a && y == b) continue;
			if(y == a && cur == b) continue;
			if(vis[y] != 2)
			{
				vis[y] = 2;
				q[++r] = y;
			}
		}
	}
	if(r + 1 != vCnt / 2)
		return 0;
	return 1;
}

int main()
{
	int T;
	int iCase = 1;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			nxt[i].clear(), deg[i] = 0;
		for(int i = 0; i < m; ++i)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			nxt[x].push_back(y);
			nxt[y].push_back(x);
			deg[x]++, deg[y]++;
		}
		memset(vis, false, sizeof vis);
		int ans = 0;
		for(int i = 1; i <= n; ++i)
		{
			if(!vis[i])
			{
				ans += solve(i);
			}
		}
		printf("Case #%d: %d\n", iCase++, ans);
	}
	return 0;
}

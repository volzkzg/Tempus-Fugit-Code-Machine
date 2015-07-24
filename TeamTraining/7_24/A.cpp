#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int Maxn = 66;
int a[Maxn][Maxn];

int deg[Maxn * Maxn];
vector<int> nxt[Maxn * Maxn];

const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

int main()
{
	int T;
	scanf("%d", &T);
	for(int cas = 1; cas <= T; ++cas)
	{
		printf("Case #%d: ", cas);
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				scanf("%d", &a[i][j]);
		for(int i = 0; i < n * m; ++i)
			nxt[i].clear(), deg[i] = 0;
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < m; ++j)
			{
				for(int k = 0; k < 4; ++k)
				{
					int nx, ny;
					nx = i + dx[k], ny = j + dy[k];
					if(nx < 0 || nx >= n || ny < 0 || ny >= m)
						continue;
					if(a[nx][ny] < a[i][j])
					{
						deg[nx * m + ny]++;
						nxt[i * m + j].push_back(nx * m + ny);
			//			printf("edge %d %d\n", i * m + j, nx * m + ny);
					}
				}	
			}
		}
		static long long f[Maxn * Maxn];
		queue<int> q;
		for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j)
		{
			f[i * m + j] = 0;
			if(deg[i * m + j] == 0)
			{
				q.push(i * m + j);
				f[i * m + j] = 1;
			}
		}
		while(!q.empty())
		{
			int cur = q.front(); 
			q.pop();
			for(int i = 0; i < nxt[cur].size(); ++i)
			{
				int y = nxt[cur][i];
				f[y] += f[cur];
				deg[y]--;
				if(!deg[y])
					q.push(y);
			}	
		}
		long long ans = 0;
		for(int i = 0; i < n * m; ++i)
			if(nxt[i].size() == 0)
			{
			//	printf("end %d\n", i);
				ans += f[i];
			}
		cout << ans << endl;
	}
	return 0;
}

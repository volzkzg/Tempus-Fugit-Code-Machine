#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

char s[1100][1100];

int mdst[1100][1100];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%s", s[i]);
	memset(mdst, 0x3f, sizeof mdst);
	queue<pair<int, int> > q;
	int startX, startY;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
		{
			if(s[i][j] == 'E')
			{
				mdst[i][j] = 0;
				q.push(make_pair(i, j));
			}
			if(s[i][j] == 'S')
			{
				startX = i, startY = j;
			}
		}
	const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
	while(!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();
		for(int i = 0; i < 4; ++i)
		{
			int nx = cur.first + dx[i], ny = cur.second + dy[i];
			if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if(s[nx][ny] == 'T') continue;
			if(mdst[nx][ny] > mdst[cur.first][cur.second] + 1)
			{
				mdst[nx][ny] = mdst[cur.first][cur.second] + 1;
				q.push(make_pair(nx, ny));
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			if(s[i][j] >= '0' && s[i][j] <= '9')
			{
				if(mdst[i][j] <= mdst[startX][startY])
				{
					ans += s[i][j] - '0';
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
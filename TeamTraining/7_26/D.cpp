#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <queue>

using namespace std;

map<long long, bool> ex;

char s[10][10];

char nxtChr()
{
	char c;
	while(true)
	{
		c = getchar();
		if(c == '.' || c == '#' || (c >= 'A' && c <= 'D'))
			return c;
	}
	return 0;
}

pair<int, int> sharp[10 * 10];
int totSharp;

void print(long long x)
{
	puts("");
	pair<int, int> pos[4];
	char m[10][10];
	for(int i = 0; i < 4; ++i)
	{
		pos[i].first = (x >> ((i * 2) * 3)) & 7;
		pos[i].second = (x >> ((i * 2 + 1) * 3)) & 7;
	}
	memset(m, 0, sizeof m);
	for(int i = 0; i < 8; ++i)
		for(int j = 0; j < 8; ++j)
		{
			m[i][j] = '.';
		}
	for(int i = 0; i < totSharp; ++i)
		m[sharp[i].first][sharp[i].second] = '#';
	for(int i = 0; i < 4; ++i)
	{
		int x = pos[i].first, y = pos[i].second;
		m[x][y] = m[x + 1][y] = m[x][y + 1] = m[x + 1][y + 1] = i + 'A';
	}
	for(int i = 0; i < 8; ++i)
		puts(m[i]);
	puts("");
}

bool overlap(int a, int b, pair<int, int> pa, pair<int, int> pb)
{
	static char s[10][10];
	s[pa.first][pa.second] = s[pa.first + 1][pa.second] = s[pa.first][pa.second + 1] = s[pa.first + 1][pa.second + 1] = 1;
	s[pb.first][pb.second] = s[pb.first][pb.second + 1] = s[pb.first + 1][pb.second] = s[pb.first + 1][pb.second + 1] = 2;
	
	if(s[pa.first][pa.second] != 1 || s[pa.first][pa.second + 1] != 1 || s[pa.first + 1][pa.second] != 1 || s[pa.first + 1][pa.second + 1] != 1)
		return true;
	return false;
}

int main()
{
	int T;
	scanf("%d", &T);
	for(int iCase = 1; iCase <= T; ++iCase)
	{
		totSharp = 0;
		printf("Case %d: ", iCase);
		ex.clear();
		for(int i = 0; i < 8; ++i)
		{
			for(int j = 0; j < 8; ++j)
			{
				s[i][j] = nxtChr();
			}
		}
		bool vis[4];
		memset(vis, 0, sizeof vis);
		long long sta = 0;
		for(int i = 0; i < 8; ++i)
			for(int j = 0; j < 8; ++j)
			{
				if(s[i][j] == '#')
				{
					sharp[totSharp++] = make_pair(i, j);
				}
				if(s[i][j] == '.' || s[i][j] == '#') continue;
				if(!vis[s[i][j] - 'A'])
				{
					vis[s[i][j] - 'A'] = true;
					int id = s[i][j] - 'A';
					sta |= (i << (id * 2 * 3)) + (j << ((id * 2 + 1) * 3));
				}
				s[i][j] = '.';
			}
		queue<long long> q;
		q.push(sta);
//		ex[sta] = true;
		static int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
		while(!q.empty())
		{
			long long cur = q.front();
			q.pop();
		//	cout << ex.size() << endl;
			for(int dir = 0; dir < 4; ++dir)
			{
				long long current = cur;
				bool change = false;
				pair<int, int> pos[4];
				for(int j = 0; j < 4; ++j)
				{
					pos[j].first = (current >> ((j * 2) * 3)) & 7;
					pos[j].second = (current >> ((j * 2 + 1) * 3)) & 7;
				}
				do
				{
					change = false;
					for(int j = 0; j < 4; ++j)
					{
						int nx, ny;
						nx = pos[j].first + dx[dir], ny = pos[j].second + dy[dir];
						if(nx < 0 || nx + 1 > 7 || ny < 0 || ny + 1 > 7) continue;
						bool succ = true;
						for(int t = 0; t < totSharp; ++t)
						{
							int sx = sharp[t].first, sy = sharp[t].second;
							if(sx >= nx && sx <= nx + 1 && sy >= ny && sy <= ny + 1)
							{
								succ = false;
								break;
							}
						}
						for(int t = 0; t < 4 && succ; ++t)
						{
							if(t == j) continue;
							if(overlap(t, j, pos[t], make_pair(nx, ny)))
							{
								succ = false;
								break;
							}
						}
						if(succ)
						{
							change = true;
							pos[j].first = nx;
							pos[j].second = ny;
						}
					}
				//	cout << "change " << change << endl;
				}while(change);
				current = 0;
				for(int i = 0; i < 4; ++i)
				{
					current |= (pos[i].first << ((i * 2) * 3));
					current |= (pos[i].second << ((i * 2 + 1) * 3));
				}
				if(ex.find(current) == ex.end())
				{
				//	print(cur);
				//	printf("--->\n");
				//	print(current);
					ex[current] = true;
					q.push(current);
				}
			}
		}
		printf("%d\n", (int)ex.size());
	}
	return 0;
}

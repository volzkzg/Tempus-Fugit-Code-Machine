#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <vector>

using namespace std;

const int Maxn = 1111, Maxm = 22;

int n, m;

char a[Maxn][Maxm];

inline bool put(int x, int y, int state)
{
	if((state & (1 << (2 * m - 1))) && x - 2 >= 0 && a[x - 1][y] == '.')
		return false;
	if((state & (1 << m - 1)) && x - 1 >= 0)
		return false;
	if((state & (1 << (m))) && x - 1 >= 0 && y - 1 >= 0)
		return false;
	if((state & (1 << (m - 2))) && x - 1 >= 0 && y + 1 < m)
		return false;
	if((state & (1 << (2 * m + 1))) && x - 2 >= 0 && y - 2 >= 0 && a[x - 1][y - 1] == '.')
		return false;
	if((state & (1 << (2 * m - 3))) && x - 2 >= 0 && y + 2 < m && a[x - 1][y + 1] == '.')
		return false;
	if((state & (1 << 1)) && y - 2 >= 0 && a[x][y - 1] == '.')
		return false;
	if((state & 1) && y - 1 >= 0)
		return false;
	return true;
}

vector<pair<int, int> > v[2];
void solve()
{
	int now = 0;
	v[now].clear();
	v[now].push_back(make_pair(0, 0));
	int mask = (1 << (2 * m + 2)) - 1;
	int ans = 0;
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			vector<pair<int, int> > &prev = v[now];
			now ^= 1; v[now].clear();
			sort(prev.begin(), prev.end());
			int size = 0;
			for (int k = 0; k < (int)prev.size(); ++k) {
				if (k == (int)prev.size() - 1 || prev[k].first != prev[k + 1].first) {
					prev[size++] = prev[k];
				}
			}
			prev.resize(size);
			for(int k = 0; k < prev.size(); ++k)
			{
				v[now].push_back(make_pair((prev[k].first << 1) & mask, prev[k].second));
				if(a[i][j] == '.' && put(i, j, prev[k].first))
				{
					v[now].push_back(make_pair((prev[k].first << 1 | 1) & mask, prev[k].second + 1));
				}
			}
		}
	}
	for(int i = 0; i < v[now].size(); ++i)
		ans = max(ans, v[now][i].second);
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		if(!n && !m)
			break;
		for(int i = 0; i < n; ++i)
			scanf("%s", a[i]);
		solve();
	}
	return 0;
}
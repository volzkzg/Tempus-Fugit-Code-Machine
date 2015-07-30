#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int Maxn = 110000;

vector<vector<int> > circ[Maxn], path[Maxn];
vector<int> single;

vector<int> nxt[Maxn];

bool vis[Maxn];

vector<int> res;

bool cmp(const vector<int> &a, const vector<int> &b)
{
	return a.size() < b.size();
}

bool dfs(int x, int pre)
{
	if(vis[x])
		return true;
	else
	{
		res.push_back(x);
		vis[x] = true;
		for(int i = 0; i < nxt[x].size(); ++i)
		{
			int y = nxt[x][i];
			if(y == pre) continue;
			return dfs(y, x);
		}
		return false;
	}
}

vector<pair<int, int> > ans;

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		nxt[x].push_back(y);
		nxt[y].push_back(x);
	}
	for(int i = 1; i <= n; ++i)
		if(nxt[i].size() == 0)
			single.push_back(i);
	for(int i = 1; i <= n; ++i)
	{
		if(!vis[i])
		{
			res.clear();
			if(dfs(i, -1))
				circ[res.size()].push_back(res);
			else
				path[res.size()].push_back(res);
		}
	}
	sort(circ.begin(), circ.end(), cmp);
	sort(path.begin(), path.end(), cmp);
	int cntEdge = 0;
	//process 3 circ
	while(circ[3].size() > 1)
	{
		cntEdge += 6;
		vector<int> a, b;
		a = circ[3][circ[3].size() - 1], b = circ[3][circ[3].size() - 2];
		circ.pop_back(), circ.pop_back();
		ans.push_back(make_pair(a[0], b[0]));
		ans.push_back(make_pair(a[1], b[0]));
		ans.push_back(make_pair(a[1], b[1]));
		ans.push_back(make_pair(a[2], b[1]));
		ans.push_back(make_pair(a[2], b[2]));
		ans.push_back(make_pair(a[0], b[2]));
	}
	if(circ[3].size())
	{
		int nxtcirc = -1;
		for(int i = 4; i <= n; ++i)
		{
			if(circ[i].size())
			{
				nxtcirc = i;
				break;
			}
		}
		if(nxtcirc != -1)
		{
			if(nxtcirc == 4)
			{
				vector<int> a, b;
				a = circ[3][0], b = circ[4][0];
				circ[4].pop_back();
				cntEdge += 7;
				ans.push_back(a[0], b[1]);
				ans.push_back(b[1], b[2]);
				ans.push_back(b[2], a[1]);
				ans.push_back(a[1], b[3]);
				ans.push_back(b[3], a[2]);
				ans.push_back(a[2], b[0]);
				ans.push_back(b[0], a[0]);
			}
			else
			{
				vector<int> a, b;
				circ[nxtcirc].pop_back();
				cntEdge += a.size() + b.size();
				vector<int> p0, p1;
				if(b.size() % 2)
				{
					for(int i = 0; i < b.size(); ++i)
						p0.push_back(i * 2 % b.size());
					ans.push_back(make_pair(p0[0], a[0]));
					ans.push_back(make_pair(a[0], p0[1]));
					ans.push_back(make_pair(p0[1], a[1]));
					ans.push_back(make_pair(a[1], p0[2]));
					ans.push_back(make_pair(p0[2], a[2]));
					ans.push_back(make_pair(a[2], p0[3]));
					for(int i = 3; i < p0.size(); ++i)
						ans.push_back(p0[i], p0[(i + 1) % p0.size()]);
				}
				else
				{
					for(int i = 0; i * 2 < b.size(); ++i)
					{
						p0.push_back(i * 2, (i + 1) * 2 % b.size());
						p1.push_back(i * 2 + 1, (i * 2 + 1) % b.size());
					}
					ans.push_back(make_pair(p0[0], a[0]));
					ans.push_back(make_pair(a[0], p0[1]));
					ans.push_back(make_pair(p0[1], a[1]));
					ans.push_back(make_pair(a[1], p0[2]));
					ans.push_back(make_pair(p0[2], a[2]));
					ans.push_back(make_pair(a[2], p0[3 % p0.size()]));
					for(int i = 3; i < p0.size(); ++i)
						ans.push_back(make_pair(p0[i], p0[(i + 1) % p0.size()]));
					for(int i = 0; i < p1.size(); ++i)
						ans.push_back(make_pair(p1[i], p1[(i + 1) % p1.size()]));
				}
			}
		}
	}
	while(circ[4].size() > 1)
	{
		vector<int> a, b;
		a = circ[4][circ[4].size() - 1], b = circ[4][circ[4].size() - 2];
	}
	return 0;
}
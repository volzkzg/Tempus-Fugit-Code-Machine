#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int Maxn = 30000;

class circle
{
public:
	int x, y, r, id;
	bool operator < (const circle &b) const
	{
		if(r == b.r)
		{
			if(x == b.x)
				return y < b.y;
			return x < b.x;
		}
		return r < b.r;
	}
	bool operator == (const circle &b) const
	{
		return r == b.r && x == b.x && y == b.y;
	}
};

circle c[Maxn];
vector<int> nxt[Maxn];

map<int, vector<int> > event;

int n;

void init()
{
	event.clear();
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		//nxt[i].clear();
		scanf("%d%d%d", &c[i].x, &c[i].y, &c[i].r);
		//event[c[i].x - c[i].r].push_back(i + 1);
		//event[c[i].x + c[i].r].push_back(-(i + 1));
		//c[i].id = i;
	}
	sort(c, c + n);
	n = unique(c, c + n) - c;
	for(int i = 0; i < n; ++i)
	{
		nxt[i].clear();
		event[c[i].x - c[i].r].push_back(i + 1);
		event[c[i].x + c[i].r].push_back(-(i + 1));
		c[i].id = i;
	}

	nxt[n].clear();
	c[n].x = c[n].y = 0, c[n].r = 40000;
	c[n].id = n;
	event[-40000].push_back(n + 1), event[40000].push_back(-n - 1);
	n++;
}

long long sqr(long long x)
{
	return x * x;
}

int lineX;

class cmp1
{
public:
	bool operator () (const circle &a, const circle &b)
	{
		double d1 = sqrt(sqr(a.r) - sqr(a.x - lineX));
		double d2 = sqrt(sqr(b.r) - sqr(b.x - lineX));
		return a.y - d1 < b.y - d2;
	}
};

class cmp2
{
public:
	bool operator () (const circle &a, const circle &b)
	{
		double d1 = sqrt(sqr(a.r) - sqr(a.x - lineX));
		double d2 = sqrt(sqr(b.r) - sqr(b.x - lineX));
		return a.y + d1 < b.y + d2;
	}
};
void build()
{
	static int fa[Maxn];
	for(int i = 0; i < n; ++i)
		fa[i] = -1;
	set<circle, cmp1> low;
	set<circle, cmp2> high;
	for(map<int, vector<int> >::iterator i = event.begin(); i != event.end(); i++)
	{
		vector<int> &t = i -> second;
		lineX = i -> first;
		int id;
		for(int j = 0; j < t.size(); ++j)
		{
			id = abs(t[j]) - 1;
		//	cout << t[j] << endl;
			if(t[j] > 0)
			{
				set<circle, cmp1>::iterator l;
				set<circle, cmp2>::iterator h;
				h = high.lower_bound(c[id]);
				if(h != high.end()) //有什么东西在上面
				{
					int hid = h -> id;
					if(c[hid].y - sqrt(sqr(c[hid].r) - sqr(c[hid].x - lineX)) - c[id].y < 0) //由于没有相切,所以直接<0
						nxt[hid].push_back(id), fa[id] = hid;
					else
					{
						{
							h = high.lower_bound(c[id]);
							bool flag2 = false;
							if(h != high.begin())
							{
								h--;
								l = low.lower_bound(c[id]);
								if(l != low.begin())
								{
									l--;
									int lid = l -> id, hid = h -> id;
									if(c[lid].y - sqrt(sqr(c[lid].r) - sqr(c[lid].x - lineX)) > c[hid].y + sqrt(sqr(c[hid].r) - sqr(c[hid].x - lineX)))
										flag2 = true;
								}
								if(!flag2)
								{
									fa[id] = fa[h -> id];
									nxt[fa[id]].push_back(id);
								}
							}
							else flag2 = true;
							if(flag2)
							{
								l = low.lower_bound(c[id]);
								if(l != low.end())
								{
									bool flag1 = false;
									h = high.lower_bound(c[id]);
									if(h != high.end())
									{
										int lid = l -> id;
										int hid = h -> id;
										if(c[lid].y - sqrt(sqr(c[lid].r) - sqr(c[lid].x - lineX)) > c[hid].y + sqrt(sqr(c[hid].r) - sqr(c[hid].x - lineX)))
											flag1 = true;
									}
									if(!flag1)
									{
										fa[id] = fa[l -> id];
										nxt[fa[id]].push_back(id);
									}
								}
							}
						}
						
					}
				}
				low.insert(c[id]), high.insert(c[id]);
			}
			else
			{
				low.erase(c[id]), high.erase(c[id]);
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
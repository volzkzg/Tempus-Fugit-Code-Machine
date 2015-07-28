#include <cstdio>
#include <set>
#include <cstring>
#include <vector>
#include <utility>

using namespace std;

const int N = 1005;
int T;
pair<int, int> part[N + 1];

int nxt[600000], ans[50000], totAns;

int val[600000];

class query
{
public:
	int ty, x;
};
query q[50000];

bool init()
{
	scanf("%d", &T);
	for(int i = 0; i <= N; ++i)
		part[i] = make_pair(10000000, -1);
	for(int i = 0; i < 600000; ++i)
		nxt[i] = i, val[i] = -1;
	for(int i = 0; i < 50000; ++i)
		ans[i] = -2;
	return T != 0;
}

int find(int x)
{
	if(nxt[x] == x) return x;
	return nxt[x] = find(nxt[x]);
}

void Union(int x, int y)
{
	nxt[find(x)] = nxt[find(y)];
}

void solve()
{
	set<pair<int, int> > totalS;
	static char s[1000];
	int tot = 0, mx = -1;
	for(int i = 0; i < T; ++i)
	{
		scanf("%s", s);
		if(s[0] == 'A')
		{
			q[i].ty = 0;
			scanf("%d", &q[i].x);
		}
		else
		{
			q[i].ty = 1;
			scanf("%d", &q[i].x);
			val[q[i].x] = ++tot;
			mx = max(mx, q[i].x);
		}
	}
	for(int i = 0; i <= mx; ++i)
		if(val[i] == -1)
			Union(i, i + 1);
	
	for(int i = T - 1; i >= 0; --i)
	{
		if(q[i].ty == 0) //'A'
		{
			int y = q[i].x;
			if(q[i].x > N)
			{
				if(tot == 0)
				{
					ans[i] = -1;
					continue;
				}
				int curAns = 2000000, curPos;
				for(int j = 0; j * y <= mx; ++j)
				{
					int pos = find(j * y);
					if(pos > mx) break;
					int v = pos % y;
					if(v <= curAns)
					{
						if(v < curAns)
							curAns = v, curPos = val[pos];
						else if(curPos < val[pos])
							curPos = val[pos];
					}
				}
				ans[i] = curPos;
			}
		}
		else
		{
			Union(q[i].x, q[i].x + 1); //del this number
			tot--;
		}
	}
	
	
	tot = 0;
	for(int i = 0; i < T; ++i)
	{
		if(q[i].ty == 0)
		{
			int y = q[i].x;
			if(q[i].x <= N)
			{
				if(tot == 0)
				{
					ans[i] = -1;
					continue;
				}
				ans[i] = part[y].second;
			}
		}
		else
		{
			++tot;
			for(int j = 1; j <= N; ++j)
			{
				int v = q[i].x % j;
				if(v <= part[j].first)
					part[j] = make_pair(v, tot);
			}
		}
	}
	
	for(int i = 0; i < T; ++i)
	{
		if(ans[i] != -2)
			printf("%d\n", ans[i]);
	}
}

int main()
{
	int iCase = 1;
	bool isFirst = true;
	while(true)
	{
		if(!init()) break;
		if(isFirst) isFirst = false;
		else puts("");
		printf("Case %d:\n", iCase++);
		solve();
	}
	return 0;
}

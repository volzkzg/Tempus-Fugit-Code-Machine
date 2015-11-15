	#include <cstdio>
	#include <cstring>
	#include <algorithm>
	#include <set>
	#include <vector>

	using namespace std;

	const int Maxn = 200000 + 100;

	set<int> s[Maxn];

	int belong[Maxn];
	int f[Maxn];

	int find(int x)
	{
		if(f[x] == x) return x;
		return f[x] = find(f[x]);
	}

	void Union(int a, int b)
	{
		f[find(a)] = f[find(b)];
	}

	void mergeSet(int x, int y)
	{
		x = belong[x], y = belong[y];
		if(x == y) return;
		if(s[x].size() > s[y].size())
			swap(x, y);
		for(set<int>::iterator i = s[x].begin(); i != s[x].end(); i++)
		{
			s[y].insert(*i);
			belong[*i] = y;
			set<int>::iterator p = s[y].find(*i);
			set<int>::iterator preP, nxtP;
			if(p != s[y].begin())
			{
				preP = p;
				preP--;
				if(*preP + 1 == *i)
				{
					Union(*preP, *i);
				}
			}
			nxtP = p;
			nxtP++;
			if(nxtP != s[y].end())
			{
				if(*i + 1 == *nxtP)
				{
					Union(*i, *nxtP);
				}
			}
		}
	}

	int main()
	{
		int n, q;
		scanf("%d%d", &n, &q);
		for(int i = 1; i <= n; ++i)
			belong[i] = i, s[i].insert(i), f[i] = i;
		for(int i = 1; i <= q; ++i)
		{
			int ty, x, y;
			scanf("%d%d%d", &ty, &x, &y);
			if(ty == 1)
			{
				mergeSet(x, y);
			}
			if(ty == 2)
			{
				int cur = x;
				while(cur <= y)
				{
					int nxt = find(cur);
					nxt++;
					if(nxt <= y)
					{
						mergeSet(cur, nxt);
					}
					cur = nxt;
				}
			}
			if(ty == 3)
			{
				if(belong[x] == belong[y])
					printf("YES\n");
				else
					printf("NO\n");
			}
		}
		return 0;
	}
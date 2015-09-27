#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

const int Maxn = 200000;

class node
{
public:
	node *l, *r;
	int size;
	int data;
	node()
	{
		size = data = 0;
		l = r = NULL;
	}
};
typedef node* tree;

node base[Maxn], *root, *null, nil, *top;

tree newNode(int data)
{
	top -> data = data;
	top -> size = 1;
	top -> l = top -> r = null;
	return top++;
}

void init()
{
	null = &nil;
	null -> l = null -> r = null;
	top = base;
}

void update(tree x)
{
	x -> size = x -> l -> size + 1 + x -> r -> size;
}

inline bool randomBySize(int a, int b)
{
	static long long seed = 1;
	return (seed = seed * 48721 % 2147483647) * (a + b) < 2147483647LL * a;
}

tree merge(tree x, tree y)
{
	if(x == null) return y;	if(y == null) return x;
	node *t;
	if(randomBySize(x -> size, y -> size)) t = x, x -> r = merge(x -> r, y);
	else t = y, y -> l = merge(x, y -> l);
	update(t);
	return t;
}

void splitBySize(tree t, int k, tree &l, tree &r)
{
	static int s; if(t == null) l = r = null;
	else if((s = t -> l -> size + 1) < k) l = t, splitBySize(t -> r, k - s, l -> r, r), update(l);
	else 						 r = t, splitBySize(t -> l, k, l, r -> l), update(r);
}

pair<int, int> p[Maxn];
int n;
int totOut;

void dfs(tree x)
{
	if(x == null) return;
	dfs(x -> l);
	totOut++;
	printf("%d%c", x -> data, totOut == n ? '\n' : ' ');
	dfs(x -> r);
}

int main()
{
	int T;
	scanf("%d", &T);
	for(int iCase = 1; iCase <= T; ++iCase)
	{
		printf("Case #%d: ", iCase);
		init();
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d%d", &p[i].first, &p[i].second);
		sort(p, p + n);
		bool succ = true;
		for(int i = n - 1, cnt = 0; succ && i >= 0; --i, cnt++)
		{
			if(i == n - 1)
			{
				root = newNode(p[i].first);
				if(p[i].second) succ = false;
			}
			else
			{
				if(p[i].second > cnt)
					succ = false;
				else
				{
					int co = p[i].second;
					int pos1 = co + 1, pos2 = cnt - co + 1;
					if(pos1 > pos2) swap(pos1, pos2);
					tree cur = newNode(p[i].first);
					if(pos1 == 0)
					{
						root = merge(cur, root);
					}
					else if(pos1 == cnt + 1)
					{
						root = merge(root, cur);
					}
					else
					{
						tree part1, part2;
						splitBySize(root, pos1, part1, part2);
						root = merge(part1, cur);
						root = merge(root, part2);
					}
				}
			}
		}
		if(!succ)
		{
			printf("impossible\n");
		}
		else
		{
			totOut = 0;
			dfs(root);
		}
	}
	return 0;
}

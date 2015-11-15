#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#include <iostream>
using namespace std;

const int Maxn = 60000;
const int MaxNode = 1000000;
const int inf = Maxn + 1;

int f[Maxn + 20];


class Point
{
public:
	int x, y;
};

Point p[Maxn];

class NodeDim1
{
public:
	NodeDim1 *lch, *rch, *fa;
	int mxPos, pos, yaxis;
	void init()
	{
		mxPos = -1;
		yaxis = pos = 0;
		fa = lch = rch = NULL;
	}
};

NodeDim1 t[MaxNode + 2 * Maxn];
int _splayTot;

NodeDim1* newSplayNode()
{
	NodeDim1* ret;
	ret = &t[_splayTot++];
	ret -> init();
	return ret;
}

class SplayDim1
{
public:
	NodeDim1 *rt;
	void init()
	{
		NodeDim1 *head, *tail;
		
		head = newSplayNode();
		tail = newSplayNode();
		
		rt = head;
		head -> rch = tail;
		head -> mxPos = 0;
		head -> pos = 0;
		head -> yaxis = -inf;
		
		tail -> fa = head;
		tail -> mxPos = Maxn + 1;
		tail -> pos = Maxn + 1;
		tail -> yaxis = inf;
	}
	
	__inline int isRight(NodeDim1 *x)
	{
		return ((x -> fa -> rch) == x);
	}
	__inline void update(NodeDim1 *x)
	{
		if(!x) return;
		NodeDim1 *l = x -> lch, *r = x -> rch;
		x -> mxPos = x -> pos;
		if(l && f[l -> mxPos] > f[x -> mxPos])
			x -> mxPos = l -> mxPos;
		else if(l && f[l -> mxPos] == f[x -> mxPos] && l -> mxPos < x -> mxPos)
			x -> mxPos = l -> mxPos;
		if(r && f[r -> mxPos] > f[x -> mxPos])
			x -> mxPos = r -> mxPos;
		else if(r && f[r -> mxPos] == f[x -> mxPos] && r -> mxPos < x -> mxPos)
			x -> mxPos = r -> mxPos;
	}
	
	void rotate(NodeDim1 *x, int isRight)
	{
		NodeDim1 *f, *g;
		f = x -> fa, g = f -> fa;
		if(g && g -> lch == f) g -> lch = x;
		else if(g && g -> rch == f) g -> rch = x;
		x -> fa = g;
		if(isRight)
		{
			f -> rch = x -> lch;
			if(x -> lch) x -> lch -> fa = f;
			f -> fa = x;
			x -> lch = f;
		}
		else
		{
			f -> lch = x -> rch;
			if(x -> rch) x -> rch -> fa = f;
			f -> fa = x;
			x -> rch = f;
		}
		update(f);
		//update(x);
		//update(g);
	}
	
	void splay(NodeDim1 *x, NodeDim1 *down)
	{
		if(down == NULL) rt = x;
		while(x -> fa != down)
		{
			NodeDim1 *f = x -> fa;
			NodeDim1 *g = f -> fa;
			if(g == down)
				rotate(x, isRight(x));
			else
			{
				if(isRight(x) == isRight(f)) rotate(f, isRight(f));
				else rotate(x, isRight(x));
				rotate(x, isRight(x));
			}
		}
		update(x);
	}
	
	NodeDim1* upper_bound(int x)
	{
		NodeDim1 *cur = rt;
		NodeDim1 *ansPos = rt;
		while(true)
		{
			if(cur -> yaxis <= x)
				cur = cur -> rch;
			else
				cur = cur -> lch;
			if(cur == NULL) break;
			if(cur -> yaxis > x)
				ansPos = cur;
		}
		return ansPos;
	}
	
	NodeDim1* lower_bound(int x)
	{
		NodeDim1 *cur = rt;
		NodeDim1 *ansPos = rt;
		while(true)
		{
			if(cur -> yaxis < x)
				cur = cur -> rch;
			else
				cur = cur -> lch;
			if(cur == NULL)
				break;
			if(cur -> yaxis >= x)
				ansPos = cur;
		}
		return ansPos;
	}
	
	NodeDim1* prev(NodeDim1 *x)
	{
		if(x -> lch == NULL)
		{
			while(x -> fa -> lch == x)
				x = x -> fa;
			return x -> fa;
		}
		else
		{
			x = x -> lch;
			while(x -> rch)
				x = x -> rch;
			return x;
		}
	}
	
	void insert(int index)
	{
		NodeDim1 *a = upper_bound(p[index].y);
		NodeDim1 *b = prev(a);
		splay(a, NULL);
		splay(b, a);
		NodeDim1 *myNewNode = newSplayNode();
		myNewNode -> yaxis = p[index].y;
		myNewNode -> mxPos = myNewNode -> pos = index;
		myNewNode -> fa = a -> lch;
		a -> lch -> rch = myNewNode;
		update(a -> lch);
		update(a);
	}
	
	int query(int l, int r)
	{
		NodeDim1 *a = lower_bound(l);
		NodeDim1 *b = upper_bound(r);
		a = prev(a);
		splay(a, NULL);
		splay(b, a);
		if(a -> rch -> lch == NULL)
			return -1;
		return a -> rch -> lch -> mxPos;
	}
	void randomSplay()
	{
		NodeDim1 *cur = rt;
		while(cur -> lch && cur -> rch)
		{
			if(rand() % 2)
				cur = cur -> lch;
			else
				cur = cur -> rch;
		}
		splay(cur, NULL);
	}
};

class NodeDim2
{
public:
	int L, R;
	SplayDim1 val;
	void init()
	{
		L = R = -1;
		val.init();
	}
};

NodeDim2 st[Maxn * 4];

int n;
const int rt = 1;

int queryCnt = 0;

class SegTreeDim2
{
public:
	void Build(int l, int r, int pos)
	{
		st[pos].init();
		st[pos].L = l, st[pos].R = r;
		if(l == r)
		{
			return;
		}
		int mid = (l + r) >> 1;
		Build(l, mid, pos << 1);
		Build(mid + 1, r, pos << 1 | 1);
	}
	void insert(int index)
	{
		int cur = rt;
		do
		{
			st[cur].val.insert(index);
			st[cur].val.randomSplay();
			int mid = st[cur].L + st[cur].R;
			mid >>= 1;
			if(p[index].x <= mid)
				cur = cur << 1;
			else
				cur = cur << 1 | 1;
		}while(st[cur].L != st[cur].R);
	}
	int query(int xl, int xr, int yl, int yr, int cur)
	{
		if(st[cur].L == xl && st[cur].R == xr)
		{
			//if(queryCnt % 1000 == 0)
			//	cerr << "queryCnt " << queryCnt << endl;
			queryCnt++;
			st[cur].val.randomSplay();
			return st[cur].val.query(yl, yr);
		}
		else
		{
			int mid = (st[cur].L + st[cur].R) >> 1;
			if(xr <= mid) return query(xl, xr, yl, yr, cur << 1);
			else if(xl > mid) return query(xl, xr, yl, yr, cur << 1 | 1);
			else
			{
				int pa = query(xl, mid, yl, yr, cur << 1);
				int pb = query(mid + 1, xr, yl, yr, cur << 1 | 1);
				if(pa == -1) return pb;
				if(pb == -1) return pa;
				if(f[pa] == f[pb])
				{
					if(pa < pb) return pa;
					return pb;
				}
				else
				{
					if(f[pa] < f[pb]) return pb;
					return pa;
				}
			}
		}
	}
}segTree;

int *lsh[Maxn];
int pre[Maxn];

bool cmp(const int *a, const int *b)
{
	return *a < *b;
}


void init(int &n)
{
	for(int i = 1; i <= n; ++i)
		scanf("%d", &p[i].x);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &p[i].y);
	n++;
	pre[n] = -1;
	p[n].x = 0, p[n].y =  1000000009;

	_splayTot = 0;
	f[0] = f[Maxn + 1] = -inf;
	segTree.Build(1, n + 10, 1);
	
	for(int i = 1; i <= n; ++i)
		lsh[i] = &p[i].x;
	sort(lsh + 1, lsh + 1 + n, cmp);

	int cur = 1, pre = *lsh[1];
	*lsh[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		if(*lsh[i] != pre)
		{
			pre = *lsh[i];
			cur++;
		}
		*lsh[i] = cur;
	}

	for(int i = 1; i <= n; ++i)
		lsh[i] = &p[i].y;
	sort(lsh + 1, lsh + 1 + n, cmp);

	cur = 1, pre = *lsh[1]; *lsh[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		if(*lsh[i] != pre)
		{
			pre = *lsh[i];
			cur++;
		}
		*lsh[i] = cur;
	}
	f[n] = 1;
	segTree.insert(n);
}


int main()
{
	while(scanf("%d", &n) == 1)
	{
		init(n);
		for(int i = n - 1; i >= 1; --i)
		{
			pre[i] = segTree.query(1, p[i].x, p[i].y, n + 1, 1);
			f[i] = f[pre[i]] + 1;
			segTree.insert(i);
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			ans = max(ans, f[i]);
		printf("%d\n", ans - 1);
		vector<int> res;
		res.clear();

		int pos = -1;
		for(int i = 1; i <= n; ++i)
			if(f[i] == ans)
			{
				pos = i;
				break;
			}
		while(pos != -1)
		{
			res.push_back(pos);
			pos = pre[pos];
		}
		for(int i = 0; i + 1 < res.size(); ++i)
			printf("%d%c", res[i], i + 2 == res.size() ? '\n' : ' ');
	}

	return 0;
}

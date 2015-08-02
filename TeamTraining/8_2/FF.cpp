#include <cstdio>
#include <cstring>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

const int MaxNum = 10000000 + 2;
const int Maxn = 200010;
int p[MaxNum], tot;
int b[MaxNum];

int a[Maxn];

const int MaxSZ = 200000;

class BIT
{
public:
	int sz;
	int f[Maxn * 2];
	void init(int n)
	{
		sz = 2 * n + 10;
		for(int i = 0; i <= sz; ++i)
			f[i] = 0;
	}
	int lowbit(int x)
	{
		return x & (-x);
	}
	void insert(int pos, int delta)
	{
		pos++;
		for(; pos <= sz; pos += lowbit(pos))
			f[pos] += delta;
	}
	int query(int pos)
	{
		pos++;
		int ret = 0;
		for(; pos; pos -= lowbit(pos))
			ret += f[pos];
		return ret;
	}
}bit;

void prepare()
{
	tot = 0;
	memset(b, 0, sizeof b);
	for(int i = 2; i < MaxNum; ++i)
	{
		if(!b[i]) p[tot++] = i;
		for(int j = 0; j < tot && 1LL * i * p[j] < MaxNum; ++j)
		{
			b[i * p[j]] = p[j];
			if(i % p[j] == 0)
				break;
		}
	}
	memset(b, 0, sizeof b);
	b[0] = b[1] = b[6] = true;
	for(int i = 0; i < tot; ++i)
		b[p[i]] = true;
	for(int i = 0; (1 << i) < MaxNum; ++i)
		b[1 << i] = true;
}

int n;

class SegTree
{
public:
	int Mx[Maxn * 2], MxPos[Maxn * 2];
	int L[Maxn * 2], R[Maxn * 2];
	
	void update(int x)
	{
		if(Mx[x << 1] > Mx[x << 1 | 1])
			Mx[x] = Mx[x << 1], MxPos[x] = MxPos[x << 1];
		else
			Mx[x] = Mx[x << 1 | 1], MxPos[x] = MxPos[x << 1 | 1]; 
	}
	void modifyEQU(int pos, int v)
	{
		int cur = 1;
		while(L[cur] != R[cur])
		{
			int mid = (L[cur] + R[cur]) >> 1;
			if(pos <= mid)
				cur = cur << 1;
			else
				cur = cur << 1 | 1;
		}
		Mx[cur] = v;
		while(cur)
		{
			cur /= 2;
			if(cur) update(cur);
		}
		int delta = b[v] - b[a[pos]];
		if(delta)
			bit.insert(pos, delta);
		a[pos] = v;
	}
	
	pair<int, int> queryMax(int l, int r, int x)
	{
		if(L[x] == l && R[x] == r)
			return make_pair(Mx[x], MxPos[x]);
		else
		{
			int mid = (L[x] + R[x]) >> 1;
			if(r <= mid) return queryMax(l, r, x << 1);
			else if(l > mid) return queryMax(l, r, x << 1 | 1);
			else return max(queryMax(l, mid, x << 1), queryMax(mid + 1, r, x << 1 | 1));
		}
	}
	
	void init(int *a, int l, int r, int x)
	{
		L[x] = l, R[x] = r;
		if(l == r)
		{
			Mx[x] = a[l];
			MxPos[x] = l;
			return;
		}
		int mid = (l + r) >> 1;
		init(a, l, mid, x << 1);
		init(a, mid + 1, r, x << 1 | 1);
		update(x);
	}
}st;

void init()
{
	bit.init(n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		if(b[a[i]])
			bit.insert(i, 1);
	}
	st.init(a, 1, n, 1);
}



void solve()
{
	int q;
	scanf("%d", &q);
	for(int i = 0; i < q; ++i)
	{
		int ty = 0;
		scanf("%d", &ty);
		if(ty == 1)
		{
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%d\n", bit.query(r) - bit.query(l - 1));
		}
		if(ty == 2)
		{
			int l, r, v;
			scanf("%d%d%d", &l, &r, &v);
			pair<int, int> res;
			while(true)
			{
				res = st.queryMax(l, r, 1);
				if(res.first < v) break;
				res.first %= v;
				st.modifyEQU(res.second, res.first);
			}
		}
		if(ty == 3)
		{
			int p, v;
			scanf("%d%d", &p, &v);
			st.modifyEQU(p, v);
		}
	}
}

int main()
{
	prepare();
	while(scanf("%d", &n) == 1)
	{
		init();
		solve();
	}
	
	return 0;
}

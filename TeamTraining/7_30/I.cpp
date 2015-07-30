#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int Maxn = 300000;

const long long inf = (1LL << 60);

class Bit
{
public:
	long long f[Maxn];
	int lim;
	inline int lowbit(int x)
	{
		return x & (-x);
	}
	void init(int n)
	{
		lim = 2 * n + 1;
		for(int i = 0; i < 2 * n + 10; ++i)
			f[i] = -inf;
	}
	void insert(int pos, long long x)
	{
		pos++;
		for(; pos <= lim; pos += lowbit(pos))
			f[pos] = max(f[pos], x);
	}
	long long query(int pos)
	{
		pos++;
		long long ret = -inf;
		while(pos)
		{
			ret = max(ret, f[pos]);
			pos -= lowbit(pos);
		}
		return ret;
	}
}bit;

int n, m;

long long d[Maxn];

class smallPath
{
public:
	int u, v, d;
	bool operator < (const smallPath &b) const
	{
		return u < b.u;
	}
}sp[Maxn];

class query
{
public:
	int u, v, id;
	long long ans;
	bool operator < (const query &b) const
	{
		return u < b.u;
	}
}q[Maxn];

bool cmp(const query &a, const query &b)
{
	return a.id < b.id;
}

void init()
{
	bit.init(n);
	for(int j = 0; j < n - 1; ++j)
	{
		int p;
		scanf("%d", &p);
		d[j + 2] = p;
	}
	for(int i = 1; i <= n; ++i)
		d[i] += d[i - 1];
	
	for(int i = 1; i <= m; ++i)
		scanf("%d%d%d", &sp[i].u, &sp[i].v, &sp[i].d);
	int Q;
	scanf("%d", &Q);
	for(int i = 1; i <= Q; ++i)
	{
		scanf("%d%d", &q[i].u, &q[i].v);
		q[i].id = i;
		q[i].ans = inf;
	}
	sort(q + 1, q + 1 + Q);
	sort(sp + 1, sp + 1 + m);
	int cur = m;
	for(int i = Q; i >= 1; --i)
	{
		while(cur >= 0 && sp[cur].u >= q[i].u)
		{
			bit.insert(sp[cur].v, (d[sp[cur].v] - d[sp[cur].u] - sp[cur].d));
			cur--;
		}
		if(q[i].u <= q[i].v)
			q[i].ans = d[q[i].v] - d[q[i].u];
		q[i].ans = min(q[i].ans, d[q[i].v] - d[q[i].u] - bit.query(q[i].v));
	}
	sort(q + 1, q + 1 + Q, cmp);
	for(int i = 1; i <= Q; ++i)
		printf("%lld\n", q[i].ans);
}

int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		init();
	}
	return 0;
}

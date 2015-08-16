#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int Maxn = 1100000;

int a[Maxn], b[Maxn], c[Maxn];

int arr[Maxn];

class BIT
{
public:
	int f[Maxn];
	int lowbit(int x)
	{
		return x & (-x);
	}
	void add(int x, int delta)
	{
		x++;
		for(; x < Maxn; x += lowbit(x))
			f[x] += delta;
	}
	int query(int x)
	{
		if(x <= 0) 	return 0;
		int ret = 0;
		x++;
		for(; x; x -= lowbit(x))
			ret += f[x];
		return ret;
	}
	void init()
	{
		memset(f, 0, sizeof f);
	}
}bit;

pair<int, int> interval[Maxn];

int ans, n;

bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
	if(a.first == b.first)
		return a.second > b.second;
	return a.first < b.first;
}

void solve()
{
	ans = 0;
	static bool del[Maxn];
	memset(del, false, sizeof del);
	for(int i = 1; i <= n; ++i)
	{
		int v = bit.query(c[i]) - bit.query(b[i] - 1);
		if(a[i] >= b[i] && a[i] <= c[i])
		{
			if(v == 1)
				del[i] = false;
			else
				del[i] = true;
		}
		else
		{
			if(v) del[i] = true;
			else del[i] = false;
		}
	}
	int tot = 0;
	for(int i = 1; i <= n; ++i)
		if(!del[i])
			interval[++tot] = make_pair(b[i], c[i]);
	sort(interval + 1, interval + tot + 1, cmp);
	int mnR = 100000000;
	
	for(int i = tot; i >= 1; --i)
	{
		if(interval[i].second >= mnR)
			del[i] = true;
		else
			del[i] = false;
		mnR = min(mnR, interval[i].second);
	}
	
	int rem = 0;
	for(int i = 1; i <= tot; ++i)
		if(!del[i])
			interval[++rem] = interval[i];
	
	sort(interval + 1, interval + 1 + rem);
	bit.init();
	for(int i = 1; i <= rem; ++i)
	{
		int v = bit.query(interval[i].second) - bit.query(interval[i].first - 1);
		if(!v)
		{
			ans++;
			bit.add(interval[i].second, 1);
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	for(int iCase = 1; iCase <= T; ++iCase)
	{
		printf("Case #%d: ", iCase);
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d%d%d", a + i, b + i, c + i), arr[i] = a[i];
		sort(arr + 1, arr + 1 + n);
		int m = unique(arr + 1, arr + 1 + n) - arr - 1;
		
		bit.init();
		for(int i = 1; i <= m; ++i)
			bit.add(arr[i], 1);
		solve();
		
		printf("%d\n", ans + m);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int Maxn = 200000;

class BIT
{
public:
	int f[Maxn];
	int sz;
	void init(int n)
	{
		sz = n + 10;
		for(int i = 0; i < sz; ++i)
			f[i] = 0;
	}
	int lowbit(int x)
	{
		return x & (-x);
	}
	void insert(int pos, int val)
	{
		pos++;
		for(; pos < sz; pos += lowbit(pos))
			f[pos] = max(f[pos], val);
	}
	int query(int pos)
	{
		pos++;
		int ret = 0;
		for(; pos; pos -= lowbit(pos))
			ret = max(ret, f[pos]);
		return ret;
	}
}bit;

int a[Maxn];
int *b[Maxn];

int LIS_end[Maxn], LIS_start[Maxn];

bool cmp(const int *a, const int *b)
{
	return *a < *b;
}

int n, l;

void prepare()
{
	bit.init(n);
	for(int i = 0; i < n; ++i)
		LIS_end[i] = 1;
	bit.insert(a[0], 1);
	for(int i = 1; i < n; ++i)
	{
		LIS_end[i] = bit.query(a[i] - 1) + 1;
		bit.insert(a[i], LIS_end[i]);
	}
	
	for(int i = 0; i < n; ++i)
		a[i] = n - a[i] + 5;
		
	for(int i = 0; i < n; ++i)
		LIS_start[i] = 1;
	bit.init(n);
	bit.insert(a[n - 1], 1);
	for(int i = n - 2; i >= 0; --i)
	{
		LIS_start[i] = bit.query(a[i] - 1) + 1;
		bit.insert(a[i], LIS_start[i]);
	}
	
	bit.init(n);
}

int main()
{
	int T;
	scanf("%d", &T);
	for(int iCase = 1; iCase <= T; ++iCase)
	{
		printf("Case #%d: ", iCase);
		scanf("%d%d", &n, &l);
		int L = l;
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		if(n == l)
		{
			printf("0\n");
			continue;
		}
		for(int i = 0; i < n; ++i)
			b[i] = &a[i];
		sort(b, b + n, cmp);
		
		int pre = *b[0]; *b[0] = 1;
		for(int i = 1; i < n; ++i)
		{
			if(pre != *b[i])
			{
				pre = *b[i];
				*b[i] = *b[i - 1] + 1;
			}
			else
				*b[i] = *b[i - 1];
		}
		
		prepare();
		
		bit.insert(a[n - 1], LIS_start[n - 1]);
		
		int ans = 0;
		
		for(int i = n - L - 2; i >= 0; --i)
		{
			ans = max(ans, LIS_end[i] + bit.query(a[i] - 1));
			bit.insert(a[i + L], LIS_start[i + L]);
		}
		for(int i = 0; i + L < n; ++i)
			ans = max(ans, LIS_end[i]);
		for(int i = L; i < n; ++i)
			ans = max(ans, LIS_start[i]);
		printf("%d\n", ans);
	}
	return 0;
}

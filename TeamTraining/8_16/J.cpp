#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int Maxn = 1100000;

class node
{
public:
	int pos;
	int val;
};

long long preSum[Maxn];
node q[Maxn];
int l, r;
int height[Maxn], n, m;

void push(int pos)
{
	while(r > l)
	{
		if(q[r].pos < pos - m + 1 || q[r].val > height[pos])
			r--;
		else
			break;
	}
	++r;
	q[r].pos = pos;
	q[r].val = height[pos];
}

int query(int pos)
{
	while(r > l)
	{
		if(q[l + 1].pos < pos - m + 1)
			l++;
		else
			break;
	}
	return q[l + 1].val;
}

void init()
{
	l = r = -1;
	static char s[Maxn];
	scanf("%s", s + 1);
	int len = strlen(s + 1);
	preSum[0] = height[0] = 0;
	int curh = 0;
	for(int i = 1; i <= len; ++i)
	{
		if(s[i] == '/')
		{	
			height[i] = curh + 1;
			curh += 2;
		}
		if(s[i] == '\\')
		{
			height[i] = curh - 1;
			curh -= 2;
		}
		if(s[i] == '_')
			height[i] = curh;
	}
	for(int i = 1; i <= len; ++i)
	{
		preSum[i] = preSum[i - 1] + height[i];
	}
	for(int i = 1; i < m; ++i)
		push(i);
}

int main()
{
	int T;
	scanf("%d", &T);
	int iCase = 0;
	while(T--)
	{
		printf("Case #%d: ", ++iCase);
		scanf("%d%d", &n, &m);
		init();
		long long ans = 1LL << 60;
		for(int i = m; i <= n; ++i)
		{
			push(i);
			long long v = query(i);
			long long s = preSum[i] - preSum[i - m];
			if(abs(v) % 2) v--;
			if(s - v * m < ans)
				ans = s - v * m;
		}
		if(ans % 2)
			cout << ans / 2 << ".5" << endl;
		else
			cout << ans / 2 << ".0" << endl;
	}
	return 0;
}

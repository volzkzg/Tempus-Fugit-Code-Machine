#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int Maxn = 2000000;

bool ex[Maxn];
int f[Maxn];

int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		int x;
		scanf("%d", &x);
		ex[x] = true;
		f[x] = 1;
	}
	int ans = 0;
	for(int i = 1; i <= 1000000; ++i)
	{
		if(ex[i])
		{
			for(int j = 2; j * i <= 1000000; ++j)
				f[j * i] = max(f[j * i], f[i] + 1);
			ans = max(ans, f[i]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
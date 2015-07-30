#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char s[100][100];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%s", s[i]);
	int ans = 0;
	for(int i = 0; i < n; ++i)
	{
		bool flag = true;
		int cnt = 0;
		for(int j = 0; j < m; ++j)
			if(s[i][j] == 'S')
			{
				flag = false;
				break;
			}
			else
			{
				if(s[i][j] == '.')
					cnt++;
			}
		if(flag)
		{
			for(int j = 0; j < m; ++j)
				s[i][j] = 0;
			ans += cnt;
		}
	}
	for(int j = 0; j < m; ++j)
	{
		bool flag = true;
		int cnt = 0;
		for(int i = 0; i < n; ++i)
		{
			if(s[i][j] == 'S')
			{
				flag = false;
				break;
			}
			else
			{
				if(s[i][j] == '.')
					cnt++;
			}
		}
		if(flag)
		{
			ans += cnt;
			for(int i = 0; i < n; ++i)
				s[i][j] = 0;
		}
	}
	printf("%d\n", ans);
	return 0;
}
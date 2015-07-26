#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int Maxn = 110;

int ori[Maxn][Maxn], tar[Maxn][Maxn];

int main()
{
	int T;
	scanf("%d", &T);
	for(int iCase = 1; iCase <= T; ++iCase)
	{
		printf("Case %d: ", iCase);
		int n, k, diff = 0;
		scanf("%d%d", &n, &k);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				scanf("%d", &ori[i][j]);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				scanf("%d", &tar[i][j]);
		bool alreadySame = true, targetSymmetric = true;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
			{
				if(ori[i][j] != tar[i][j])
					alreadySame = false;
				if(tar[i][j] != tar[j][i])
					targetSymmetric = false;
				diff += (ori[i][j] != tar[i][j]);
			}
		if(alreadySame)
		{
			printf("0\n");
			continue;
		}
		if(targetSymmetric)
		{
			printf("-1\n");
			continue;
		}
		if(k == 2)
		{
			int ans = -1;
			if(n == 2)
			{
				if(tar[0][1] != ori[0][1] && tar[1][0] != ori[1][0])
					printf("-1\n");
				else
				{
					printf("%d\n", diff);
				}
				continue;
			}
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j)
				{
					if(i == j) continue;
					if(tar[i][j] != ori[j][i]) //can change directly
					{
						ans = diff;
						break;
					}
				}
			if(ans == -1)
			{
				int cnt = 0;
				for(int i = 0; i < n; ++i)
				{
					for(int j = 0; j < i; ++j)
					{
						if(ori[i][j] != ori[j][i]) cnt++;
					}
				}
				if(cnt > 1)
					ans = diff;
			}
			if(ans == -1)
				ans = diff + 2;
			printf("%d\n", ans);
			continue;
		}
		else
		{
			int ans = -1;
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j)
				{
					if(i == j) continue;
					if(tar[i][j] != ori[j][i])
					{
						ans = diff;
						break;
					}
				}
			if(ans == -1)
			{
				int cnt = 0;
				for(int i = 0; i < n; ++i)
					for(int j = 0; j < i; ++j)
					{
						if(i == j) continue;
						if(ori[i][j] != ori[j][i]) cnt++;
					}
				if(cnt > 1)
					ans = diff;
			}
			if(ans == -1)
				ans = diff + 1;
			printf("%d\n", ans);
			continue;
		}
	}
	return 0;
}

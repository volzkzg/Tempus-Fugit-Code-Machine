#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
char s[110][110];

int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%s", s[i]);
	//all rows
	bool succRow = true;
	for(int i = 0; i < n; ++i)
	{
		bool ex = false;
		for(int j = 0; j < n; ++j)
			if(s[i][j] == '.')
			{
				ex = true;
				break;
			}
		if(!ex)
		{
			succRow = false;
			break;
		}
	}
	if(succRow)
	{
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				if(s[i][j] == '.')
				{
					printf("%d %d\n", i + 1, j + 1);
					break;
				}
			}
		}
		return 0;
	}
	//all cols
	bool succCol = true;
	for(int j = 0; j < n; ++j)
	{
		bool ex = false;
		for(int i = 0; i < n; ++i)
			if(s[i][j] == '.')
			{
				ex = true;
				break;
			}
		if(!ex)
		{
			succCol = false;
			break;
		}
	}
	if(succCol)
	{
		for(int j = 0; j < n; ++j)
			for(int i = 0; i < n; ++i)
			{
				if(s[i][j] == '.')
				{
					printf("%d %d\n", i + 1, j + 1);
					break;
				}
			}
		return 0;
	}
	printf("-1\n");
	return 0;
}
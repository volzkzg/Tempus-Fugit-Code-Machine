#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int f[400][400];

map<int, int> mapping, revese_map;

pair<int, int> light[300];

int a[300], l[300], r[300];

int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &light[i].first, &light[i].second);
	sort(light, light + n);
	int tot = 1;
	for(int i = 1; i <= n; ++i)
	{
		int a, b, c;
		a = light[i].first;
		b = light[i].first - light[i].second;
		c = light[i].first + light[i].second;
		mapping[a] = mapping[b] = mapping[c] = 1;
	}
	for(map<int, int>::iterator i = mapping.begin(); i != mapping.end(); i++)
	{
		i -> second = tot;
		reverse_map[tot++] = i -> first;
	}
	for(int i = 1; i <= n; ++i)
	{
		a[i] = mapping[light[i].first];
		l[i] = mapping[light[i].first - light[i].second];
		r[i] = mapping[light[i].first + light[i].second];
	}
	memset(f, -1, sizeof f);
	f[0][0] = 0;
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < tot; ++j)
		{
			if(f[i][j] == -1) continue;
			const int &cur = f[i][j];
			for(int k = i + 1; k <= n; ++k)
			{
				if(r[k] > j)
					f[k][r[k]] = max(f[k][r[k]], cur + reverse_map[r[k]] - max(reverse_map[a[k]], reverse_map[j]));
				else
					f[k][j] = max(f[k][j], cur);
				if(l[k] > j)
					f[k][l[k]] = max(f[l][l[k]], cur + reverse_map[a[k]] - reverse_map[l[k]]);
				else
					f[k][j] = max(f[k][j], cur);
			}
		}
	}
	return 0;
}

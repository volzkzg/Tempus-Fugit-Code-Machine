#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <cstdio>
using namespace std;

const long long inf = (1LL << 61);

long long f[51][51][33];
long long g[51][51];

class NegativeGraphDiv1
{
public:
	
	long long findMin(int N, vector <int> from, vector <int> to, vector <int> weight, int charges)
	{
		from.push_back(N);
		to.push_back(N);
		weight.push_back(0);
		int E = from.size();
		for(int i = 0; i < 51; ++i)
			for(int j = 0; j < 51; ++j)
			{
				g[i][j] = inf;
				if(i == j)
					g[i][j] = 0;
				for(int k = 0; k < 33; ++k)
					f[i][j][k] = inf;
			}
		for(int i = 0; i < E; ++i)
			from[i]--, to[i]--;
		for(int i = 0; i < E; ++i)
			g[from[i]][to[i]] = min(g[from[i]][to[i]], (long long)weight[i]);
		for(int k = 0; k < N; ++k)
			for(int i = 0; i < N; ++i)
				for(int j = 0; j < N; ++j)
					g[i][j] = min(g[i][k] + g[k][j], g[i][j]);
	//	for(int i = 0; i < N; ++i)
	//		for(int j = 0; j < N; ++j)
	//			cout << "g[" << i << "][" << j << "] = " << g[i][j] << endl;
		for(int i = 0; i < E; ++i)
		{
			for(int j = 0; j < N; ++j)
				for(int k = 0; k < N; ++k)
				{
					f[j][k][0] = min(f[j][k][0], g[j][from[i]] - weight[i] + g[to[i]][k]);
	//				printf("f[%d][%d][%d] = %lld\n", j, k, 0, f[j][k][0]);
				}
		}
		for(int k = 1; k < 31; ++k)
		{
			for(int p = 0; p < N; ++p)
				for(int i = 0; i < N; ++i)
					for(int j = 0; j < N; ++j)
						f[i][j][k] = min(f[i][j][k], f[i][p][k - 1] + f[p][j][k - 1]);
		}
		map<int, long long> dst[53];
		for(int i = -1; i < 33; ++i)
			for(int j = 0; j < 53; ++j)
				dst[j][i] = inf;
		for(int j = 0; j < N; ++j)
			dst[j][-1] = g[0][j];
		for(int i = 0; i < 31; ++i)
		{
			if((charges >> i) & 1)
			{
				for(int j = 0; j < N; ++j)
				{
					for(int k = 0; k < N; ++k)
						dst[k][i] = min(dst[k][i], dst[j][i - 1] + f[j][k][i]);
				}
			}
			else
			{
				for(int j = 0; j < N; ++j)
					dst[j][i] = dst[j][i - 1];
			}
		}
		return dst[N - 1][30];
	}
};
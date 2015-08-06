#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long f[11][10];
long long f2[11][10];
long long g[11];

void prepare()
{
	g[0] = 1;
	for(int i = 1; i < 11; ++i)
		g[i] = g[i - 1] * 10;
	for(int i = 0; i <= 9; ++i)
		f[1][i] = 1, f2[1][i] = 1;
	for(int i = 2; i < 11; ++i)
	{
		for(int j = 0; j <= 9; ++j)
		{
			f2[i][j] = f2[i - 1][j] * 10;
		}
		for(int j = 0; j <= 9; ++j)
		{
			f2[i][j] += g[i - 1];
		}
	}
	memcpy(f, f2, sizeof f);
	for(int i = 2; i < 11; ++i)
	{
		for(int j = 1; j < i; ++j)
		{
			f[i][0] -= g[i - j];
		}
	}
/*	for(int i = 1; i < 11; ++i)
	{
		for(int j = 0; j <= 9; ++j)
		{
			if(j % 3 == 0)
				puts("");
			printf("f[%d][%d] = %d,", i, j, f[i][j]);
		}
	}*/
}

vector<int> solve(long long x)
{
	int len = 0;
	long long tmp = x;
	int Bit[11];
	vector<int> ret;
	ret.resize(10);
	for(int i = 0; i < 10; ++i)
		ret[i] = 0;
	if(x == 0)
	{
		ret[0] = 1;
		return ret;
	}
	if(x == -1) return ret;
	while(tmp)
	{
		len++;
		Bit[len] = tmp % 10;
		tmp /= 10;
	}
	long long pre[11];
	memset(pre, 0, sizeof pre);
	for(int i = len; i > 0; --i)
	{
		for(int j = 0; j < Bit[i]; ++j)
		{
			if(!(i == len && j == 0))
				ret[j] += g[i - 1];
			if(len == 1 && j == 0)
				ret[j] += g[i - 1];
			for(int k = 0; k < 10; ++k)
			{
				if(i != len || j != 0)
					ret[k] += f2[i - 1][k];
				else
					ret[k] += f[i - 1][k];
			}
			for(int p = 0; p < 10; ++p)
				ret[p] += g[i - 1] * pre[p];
		}
		pre[Bit[i]]++;
	}
	for(int i = 0; i < 10; ++i)
		ret[i] += pre[i];
	return ret;
}

int main()
{
	ios::sync_with_stdio(false);
	prepare();
	while(true)
	{
		long long a, b;
		cin >> a >> b;
		if(a > b) swap(a, b);
		if(a == 0 && b == 0) break;
		vector<int> A = solve(a - 1);
		vector<int> B = solve(b);
		for(int i = 0; i < 9; ++i)
			cout << B[i] - A[i] << ' ';
		cout << B[9] - A[9] << endl;
	}
	return 0;
}

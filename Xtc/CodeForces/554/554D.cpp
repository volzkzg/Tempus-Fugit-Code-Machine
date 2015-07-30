#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <cassert>

using namespace std;

const int Maxn = 100;

const long long Lim = 3000000000000000000LL; //3e18

long long f[Maxn];

void Count(int x) {
	if(f[x] != -1) return;
	f[x] = 0;
	for(int i = 1; i <= 2 && i <= x; ++i) {
		Count(x - i);
		f[x] += f[x - i];
		if(f[x] > Lim) {
			f[x] = Lim;
			return;
		}
	}
}

vector<int> solve(int n, long long k) {
	if(n == 1)
		return vector<int> (1, 1);
	else
	{
		if(n == 0)
		{
			assert(k <= 1);
			return vector<int>(0,1);
		}
		long long sum = 0;
		vector<int> ret, tmp;
		for(int i = 1; i <= n; ++i)
		{
			if(f[n - i] + sum >= k)
			{
				for(int j = 1; j < i; ++j)
					ret.push_back((j + 1));
				ret.push_back(1);
				tmp = solve(n - i, k - sum);
				for(int j = 0; j < tmp.size(); ++j)
					ret.push_back(tmp[j] + i);
				return ret;
			}
			else
			{
				sum += f[n - i];
			}
		}
		for(int j = 1; j < n; ++j)
			ret.push_back(j + 1);
		ret.push_back(1);
	}
}

int main() {
	memset(f, -1, sizeof f);
	f[0] = 1;
	f[1] = 1;
	for(int i = 1; i <= 50; ++i)
		Count(i);
	int n;long long k;
	cin >> n >> k;
	vector<int> ans = solve(n, k);
	for(int i = 0; i < ans.size(); ++i)
		printf("%d%c", ans[i], i + 1 == ans.size() ? '\n' : ' ');
	return 0;
}
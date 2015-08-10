#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1000;
bool isPrime[N];
int prime[N], primeCnt;
long long have[N];
int n, ans[N], final_ans;
vector<int> v;

void dfs(int last, int sum, long long use)
{
	ans[sum]++;
	for (int i = last; i >= 2; --i) {
		if ((use & have[i]) == 0 && sum + i <= n) {
			
			dfs(i - 1, sum + i, use | have[i]);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	memset(isPrime, true, sizeof(isPrime));
	isPrime[1] = false;
	for (int i = 2; i < N; ++i) {
		if (isPrime[i]) {
			prime[++primeCnt] = i;
			for (int j = i + i; j < N; j += i)
				isPrime[j] = false;
		}
	}
	cin >> n;
	for (int i = 2; i <= n; ++i) {
		int now = i;
		int pos = 1;
		while (now > 1) {
			if (now % prime[pos] == 0) {
				have[i] |= (1LL << (pos - 1));
				while (now % prime[pos] == 0)
					now /= prime[pos];
			}
			pos++;
		}
	}

	dfs(n, 0, 0);
	for (int i = 0; i <= n; ++i) 
		final_ans += ans[i];
	cout << final_ans << endl;
	return 0;
}

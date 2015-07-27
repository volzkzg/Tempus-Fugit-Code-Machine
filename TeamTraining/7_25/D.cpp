#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const int mod = 1000000007;
const int modx = -mod;
const int N = 91111;
int dp[N], sum[2][N];
int num[300];

int main()
{
	int t, n;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		int total = 0;
		for(int i = 1; i <= n; i++){
			scanf("%d", &num[i]);
			total += num[i];
		}
		if(total & 1) total++;
		memset(dp, 0, sizeof(dp));
		memset(sum, 0, sizeof(sum));
		dp[total] = 1;
		int tt = total * 2;
		for(int i = 1; i <= n; i++){
			sum[0][0] = dp[0];
			sum[1][0] = 0;
			for(int j = 1;j <= tt; j++){
				sum[0][j] = sum[0][j-1];
				sum[1][j] = sum[1][j-1];
				sum[j&1][j] += dp[j];
				sum[j&1][j] %= modx;
			}
			long long ans = 0;
			for(int j = 0;j <= num[i]; j++){
				ans += (long long)dp[j] * ((num[i] - j) / 2 + 1);
				ans %= mod;
			}
			int p = (num[i] & 1) ^ 1;
			int res = ans;
			for(int j = 0;j <= tt; j++){
				dp[j] = res;
				int u = j - num[i] - 1;
				u = max(u, 0);
				res += (sum[p][j + 1 + num[i]] - sum[p][j]) % mod;
				res %= mod;
				p ^= 1;
				res -= (sum[p][j] - sum[p][u])%mod;
				res %= mod;
			}
		}
		int res = dp[total];
		res %= mod;
		res = (res + mod) % mod;
		cout << res << endl;
	}
	return 0;
}


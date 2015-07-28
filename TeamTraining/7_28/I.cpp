#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<int> arr_p;
int p, n;

int C[1100][1100];

bool init()
{
	scanf("%d%d", &p, &n);
	if(p == 0 && n == 0) return false;
	int N = n;
	arr_p.clear();
	while(N)
	{
		arr_p.push_back(N % p);
		N /= p;
	}
	for(int i = 0; i <= p; ++i)
		for(int j = 0; j <= p; ++j)
			C[i][j] = 0;
	for(int i = 0; i <= p; ++i)
	{
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; ++j)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % p;
	}
	return true;
}

void solve()
{
	int ans = 0, pPower = 1;
	int cnt = 1, now, cntFull = 1, nowFull;

	for(int i = 0; i < arr_p.size(); ++i)
	{
		now = 0; nowFull = 0;
		for(int j = 0; j < p; ++j)
		{
			if(C[arr_p[i]][j] != 0)
			{
				if(j <= arr_p[i])
					now++;
				nowFull++;
				continue;
			}
			if(j < arr_p[i])
			{
				ans += (n / (pPower) / p + 1) * cntFull;
			}
			else if(j == arr_p[i])
			{
				ans += (n / (pPower) / p) * cntFull;
				ans += cnt;
			}
			else if(i + 1 != arr_p.size()) //not last digit
			{
				ans += (n / (pPower) / p) * cntFull;
			}
		}
		cnt = cnt * now;
		cntFull = cntFull * nowFull;
		pPower *= p;
	}
	ans = n + 1 - ans; //non-zero
	ans = ans % 10000;
	printf("%04d\n", ans);
}

int main() {
	int iCase = 1;
	while(true)
	{
		if(!init()) break;
		printf("Case %d: ", iCase++);
		solve();
	}
	return 0;
}

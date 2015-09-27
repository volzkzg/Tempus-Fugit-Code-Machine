#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int MAXN = 63;

int D, S1, S2;
int tst_case;
int a[MAXN], cnt, num;
int sum[MAXN];
int cur[MAXN];

bool Justify(int i) {
	int tmp = sum[num] - sum[i - 1];
	tmp++;
	if ((tmp <= S1 && tmp + (i - 1) >= S1) || (tmp <= S2 && tmp + (i - 1) >= S2) ||
	    (tmp >= S1 && tmp <= S2) || (tmp + (i - 1) >= S1 && tmp + (i - 1) <= S2)) {
		a[i] = 1;
		for (int j = 1; j < i; ++j)
			a[j] = 0;
		for (int j = 1; j <= S1 - tmp; ++j)
			a[j] = 1;
		return true;
	}
	else 
		return false;
}

int main() {
	scanf("%d", &tst_case);
	for (int tt = 1; tt <= tst_case; ++tt) {
		scanf("%d%d%d", &D, &S1, &S2);
	        num = 0;
		while (D) {
			a[++num] = (D & 1);
			D >>= 1;
		}
		a[++num] = 0;
		sum[0] = 0;
		for (int i = 1; i <= num; ++i)
			sum[i] = sum[i - 1] + (a[i] == 1);
		for (int i = 1; i <= num; ++i)
			if (a[i] == 0) {
				if (Justify(i))
					break;
			}
		long long ans = 0;
		for (int i = num; i; --i)
			if (a[i] == 1)
				ans |= (1LL << (i - 1));
		printf("Case #%d: %I64d\n", tt, ans);
	}

	return 0;
}

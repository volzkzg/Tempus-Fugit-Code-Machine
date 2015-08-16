#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 1000 + 10;

int tst_case;
int a[MAXN], ans, n, k;

int main() {
	scanf("%d", &tst_case);
	for (int tt = 1; tt <= tst_case; ++tt) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		sort(a + 1, a + 1 + n);
		int last = a[1];
		ans = 1;
		for (int i = 2; i <= n; ++i) {
			if (last + k < a[i])
				ans++;
			last = a[i];
		}
		printf("Case #%d: %d\n", tt, ans);
	}
	return 0;
}

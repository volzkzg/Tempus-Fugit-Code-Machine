#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int tst, a, b, c, d, e, m;

int main() {
	scanf("%d", &tst);
	int tt = 0;
	while (tst--) {
		scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &m);
		int sum = a + b + c + d + e;
		printf("Case #%d: ", ++tt);
		if (sum == 0) {
			if (m <= 0) puts("0");
			else puts("-1");
		}
		else if (sum < 0) {
			if (m > sum) {
				puts("-1");
			} else {
				int ans = 0;
				for (;;) {
					if (sum >= m) break;
					ans++;
					sum = sum * 2;
				}
				printf("%d\n", ans);
			}
		}
		else {
			int ans = 0;
			for (;;) {
				if (sum >= m) break;
				ans++;
				sum = sum * 2;
			}
			printf("%d\n", ans);
		}
	}

	return 0;
}

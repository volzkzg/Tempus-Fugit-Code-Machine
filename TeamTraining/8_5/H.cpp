#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

const int MAXN = 100 + 10;

int a[MAXN], tmp[MAXN];
int n, d, b[MAXN][MAXN];

int main() {
	int T = 100000;
	scanf("%d%d", &n, &d);
	for (int i = 1; i < d; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", &b[i][j]);
	srand(time(NULL));
	bool ans = true;
	while (T--) {
		for (int i = 1; i <= n; ++i)
			a[i] = i;
		random_shuffle(a + 1, a + 1 + n);
		
		for (int i = d - 1; i >= 1; --i) {
			for (int j = 1; j <= n; ++j)
				tmp[j] = a[j];
			sort(tmp + 1, tmp + n / 2 + 1);
			sort(tmp + n / 2 + 1, tmp + n + 1);
			for (int j = 1; j <= n; ++j)
				a[j] = tmp[b[i][j]];
		}
		sort(a + 1, a + n / 2 + 1);
		sort(a + n / 2 + 1, a + n + 1);
		for (int i = 1; i <= n; ++i)
			if (a[i] != i) {
				ans = false;
				break;
			}
		if (ans == false)
			break;
	}
	if (ans)
		puts("Yes");
	else
		puts("No");

	return 0;
}


C#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAXN = 500 + 10;

int n, m, k;
int vis[50000000];

int main() {
	int tt = 0;
	while (scanf("%d%d%d", &n, &m, &k) == 3) {
		if (n == 0 && m == 0 && k == 0)
			break;
		int ans = 0;
		for (int a, b, c, i = 1; i <= n; ++i) {
			scanf("%d%d%d", &a, &b, &c);
			if (b == 1) ++ans;
			if (c == 1) ++ans;
		}
		for (int i = 1; i <= n; ++i)
			vis[i] = 0;
		for (int a, b, i = 1; i <= m; ++i) {
			scanf("%d%d", &a, &b);
			if (b >= k)
				vis[a] = 1;
		}
		for (int i = 1; i <= n; ++i)
			if (vis[i])
				++ans;
		printf("Case %d: %d\n", ++tt, ans);
	}
	for (int i = 1; i <= 40000; ++i) {
		int pos = i * 1000;
		vis[pos] = k;
		cout << vis[pos] << endl;
	}
	return 0;
}

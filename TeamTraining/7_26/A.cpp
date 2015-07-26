#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 1000 + 10;

int n, a[MAXN];
bool vis[MAXN];

int main() {
	int tt = 0;
	while (scanf("%d", &n) == 1) {
		if (!n) break;
		int ans = 0;
		//		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			if (a[i] > 0) {
				++ans;
				//	vis[a[i]] = 1;
			}
			else if (a[i] == 0) {
				--ans;
			}
		}
		printf("Case %d: %d\n", ++tt, ans);
	}
	
	return 0;
}

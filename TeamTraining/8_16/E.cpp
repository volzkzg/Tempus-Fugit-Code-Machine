#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 20000 + 10;

int fa[MAXN], father[MAXN];
int n, Q, tst_case;
int qry[MAXN][3], ans[MAXN];
int mark[MAXN];

int getfather(int x) {
	return (father[x] == x) ? x : father[x] = getfather(father[x]);
}

char str[10];

int main() {
	scanf("%d", &tst_case);
	for (int tt = 1; tt <= tst_case; ++tt) {
		scanf("%d%d", &n, &Q);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &fa[i]);
		for (int i = 1; i <= n; ++i)
			father[i] = i, mark[i] = 0;
		for (int i = 1; i <= Q; ++i) {
			scanf("%s", str + 1);
			if (str[1] == 'Q') {
				qry[i][0] = 1;
				scanf("%d%d", &qry[i][1], &qry[i][2]);
			}
			else {
				qry[i][0] = 2;
				scanf("%d", &qry[i][1]);
				if (mark[qry[i][1]] == 0)
					mark[qry[i][1]] = i;
			}
		}
		for (int i = 1; i <= n; ++i)
			if (fa[i] != 0 && !mark[i])
				father[i] = fa[i];
		for (int i = 1; i <= Q; ++i)
			ans[i] = 0;
		for (int i = Q; i; --i) {
			if (qry[i][0] == 1) {
				int p = getfather(qry[i][1]), q = getfather(qry[i][2]);
				if (p == q)
					ans[i] = 1;
				else
					ans[i] = 0;
			}
			else {
				int p = qry[i][1];
				if (fa[p] != 0 && mark[p] == i)
					father[p] = fa[p];
			}
		}
		printf("Case #%d:\n", tt);
		for (int i = 1; i <= Q; ++i)
			if (qry[i][0] == 1) {
				if (ans[i])
					puts("YES");
				else
					puts("NO");
			}
	}

	return 0;
}

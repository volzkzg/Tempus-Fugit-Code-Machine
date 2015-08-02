#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 50000 + 10;
const int INF = 0x7FFFFFFF >> 2;

int m1[MAXN], m2[MAXN];
int n, m, q;
pair <int, int> P[MAXN];

int main () {
	while (scanf("%d%d%d", &n, &m, &q) == 3) {
		for (int a, b, i = 1; i <= m; ++i) {
			scanf("%d%d", &a, &b);
			P[i] = make_pair(-a, b);
		}
		sort(P + 1, P + 1 + m);
		for (int i = 1; i <= n + 1; ++i)
			m1[i] = m2[i] = INF;
		int st = 1;
		for (int i = n; i; --i) {
			m1[i] = m1[i + 1];
			m2[i] = m2[i + 1];
			if (st > m || i != -P[st].first)
				continue;
			int ed = st;
			while (ed + 1 <= m && P[ed + 1].first == P[ed].first)
				++ed;
			for (int j = st; j <= ed; ++j) {
				if (P[j].second < m1[i]) {
					m2[i] = m1[i];
					m1[i] = P[j].second;
				}
				else if (P[j].second < m2[i]) {
					m2[i] = P[j].second;
				}
			}
			st = ed + 1;
		}
		for (int a, i = 1; i <= q; ++i) {
			scanf("%d", &a);
			int ans = a - m2[a];
			if (ans <= 0) {
				puts("0");
			}
			else
				printf("%d\n", ans);
		}
	}
        return 0;
}

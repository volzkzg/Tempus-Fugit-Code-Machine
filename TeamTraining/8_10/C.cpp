#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2000 + 10;

bool dp[MAXN][MAXN];
vector <int> G[MAXN], ans1, ans2;
pair <int, int> last[MAXN][MAXN];
int n, m, A, B, C, D;

bool Solve() {
	dp[A][C] = 1;
	for (int i = A; i <= B; ++i)
		for (int j = C; j <= D; ++j) {
			if (!dp[i][j])
				continue;
			if (i != B && (j == D || i < j)) {
				for (int k = 0; k < (int)G[i].size(); ++k) {
					int v = G[i][k];
					if (v == j)
						continue;
					dp[v][j] = 1;
					last[v][j] = make_pair(i, j);
				}
			}
			else {
				for (int k = 0; k < (int)G[j].size(); ++k) {
					int v = G[j][k];
					if (v == i)
						continue;
					dp[i][v] = 1;
					last[i][v] = make_pair(i, j);
				}
			}
		}
	return dp[B][D];
}

int main() {
	freopen("express.in", "r", stdin);
	freopen("express.out", "w", stdout);
	scanf("%d%d", &n, &m);
	scanf("%d%d%d%d", &A, &B, &C, &D);
	if (A > B)
		swap(A, B);
	if (C > D)
		swap(C, D);
	for (int a, b, i = 1; i <= m; ++i) {
		scanf("%d%d", &a, &b);
		if (a > b)
			swap(a, b);
		G[a].push_back(b);
	}
	if (Solve()) {
		puts("YES");
		while (A != B || C != D) {
			pair <int, int> tmp = last[B][D];
			if (tmp.first == B)
				ans2.push_back(D);
			else
				ans1.push_back(B);
			B = tmp.first;
			D = tmp.second;
		}
		ans1.push_back(A);
		ans2.push_back(C);
		reverse(ans1.begin(), ans1.end());
		reverse(ans2.begin(), ans2.end());
		printf("%d", ans1[0]);
		for (int i = 1; i < (int)ans1.size(); ++i)
			printf(" %d", ans1[i]);
		printf("\n%d", ans2[0]);
		for (int i = 1; i < (int)ans2.size(); ++i)
			printf(" %d", ans2[i]);
		printf("\n");
	}
	else
		puts("NO");
	
	return 0;
}

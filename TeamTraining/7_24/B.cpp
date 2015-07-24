#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 100000 + 10;
vector<int> g[N];
int n;

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		static int tst = 0;
		++tst;
		cout << "Case #" << tst << ": ";
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			g[i].clear();
		}
		int minus = 0, ans = 0;
		for (int i = 1; i < n; ++i) {
			int u, v, w;
			cin >> u >> v >> w;
			g[u].push_back(w);
			g[v].push_back(w);
			minus += w;
		}
		for (int i = 1; i <= n; ++i) {
			int max_num = 0;
			int sum = 0, other;
			for (int j = 0; j < (int)g[i].size(); ++j) {
				int w = g[i][j];
				max_num = max(max_num, w);
				sum += w;
			}
			other = sum - max_num;
			if (max_num > other) {
				ans += max_num;
			} else {
				ans += (sum + 1) / 2;
			}
		}
		cout << ans - minus << endl;
	}
	return 0;
	
}

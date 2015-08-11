#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 200;
int n, k, father[N], root, size[N], cnt;
vector<int> G[N];

void dfs(int u)
{
	size[u] = 1;
	for (int i = 0; i < (int)G[u].size(); ++i) {
		int v = G[u][i];
		dfs(v);
		size[u] += size[v];
	}
	if (size[u] == k + 1) cnt++;
}

int main()
{
	ios::sync_with_stdio(false);
	while (cin >> n >> k) {
		for (int i = 1; i <= n; ++i) {
			G[i].clear();
			father[i] = -1;
		}
		for (int i = 1; i < n; ++i) {
			int u, v;
			cin >> u >> v;
			G[u].push_back(v);
			father[v] = u;
		}
		for (int i = 1; i <= n; ++i) {
			if (father[i] == -1) {
				root = i;
				break;
			}
		}
		cnt = 0;
		dfs(root);
		cout << cnt << endl;
	}
	return 0;
	
}
	

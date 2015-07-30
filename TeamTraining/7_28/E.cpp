#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int INF = 0x7FFFFFFF/2;
const int N = 111, M = 555, K = 20, T = 120;
struct Edge {
	int v, w, c;
	Edge() {}
	Edge(int _v, int _w, int _c):v(_v), w(_w), c(_c) {}
};
int n, m, k, t;
int G[N][N], dist_ed[N];
vector<Edge> Graph[N];
struct Status {
	long long val;
	int pos;
	Status() {}
	Status(long long _val, int _pos):val(_val), pos(_pos) {}
	bool operator < (const Status &rhs) const {
		long long num1 = val + dist_ed[pos];
		long long num2 = rhs.val + dist_ed[rhs.pos];
		if (num1 == num2) {
			return pos > rhs.pos;
		} else {
			return num1 > num2;
		}
	}
};

void init()
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			if (i == j)
				G[i][j] = 0;
			else
				G[i][j] = INF;
		}
	for (int i = 0; i < n; ++i)
		Graph[i].clear();
	for (int i= 1; i <= m; ++i) {
		int u, v, w, c;
		scanf("%d%d%d%d", &u, &v, &c, &w);
		Graph[u].push_back(Edge(v, w, c));
		G[v][u] = min(G[v][u], w);
	}
}

void dijkstra()
{
	static bool vis[N];
	memset(vis, false, sizeof(vis));
	for (int i = 0; i < n - 1; ++i)
		dist_ed[i] = INF;
	dist_ed[n - 1] = 0;
	for ( ; ; ) {
		int pos = -1;
		for (int i = 0; i < n; ++i) {
			if (vis[i]) continue;
			if (pos == -1 || dist_ed[i] < dist_ed[pos]) {
				pos = i;
			}
		}
		if (pos == -1) break;
		vis[pos] = true;
		for (int i = 0; i < n; ++i)
			if (dist_ed[pos] + G[pos][i] < dist_ed[i])
				dist_ed[i] = dist_ed[pos] + G[pos][i];
	}
}

void solve()
{
	++k;
	dijkstra();
	priority_queue<Status> q;
	map<Status, int> times_in_que;
	vector<long long> ans;
	q.push(Status(0, 0));
	times_in_que[Status(0, 0)] = 1;

	while (!q.empty()) {
		Status now = q.top(); q.pop();
		int &temp = times_in_que[now];
		int times_now = temp;
		temp = 0;
		//cout << "Begin " << now.pos << " " << now.val << endl;

		int u = now.pos;
		long long val = now.val;

		if (u == n - 1) {
			for (int i = 0; i < times_now; ++i)
				ans.push_back(val);
			if ((int)ans.size() >= k) break;
		}

		//cout << (int)Graph[u].size() << endl;
		for (int i = (int)Graph[u].size() - 1; i >= 0; --i) {
			//for (int i = 0; i < (int)Graph[u].size(); ++i) {
			int v = Graph[u][i].v;
			int w = Graph[u][i].w;
			int c = Graph[u][i].c;
			//cout << u << " " << v << " " << w << " " << c << endl;
			for (long long start = (val + c - 1) / c * c;
			     start - val <= t;
			     start += c) {
				Status next = Status(start + w, v);
				int &times = times_in_que[next];
				if (times == 0) {
					//cout << "Insert " << start + w << " " << v << endl;
					q.push(next);
				}
				times += times_now;
				times = min(times, 10);
			}
		}
	}

	//cout << (int)ans.size() << " " << k << endl;
	sort(ans.begin(), ans.end());
	if ((int)ans.size() < k) {
		printf("-1\n");
	} else {
		printf("%lld\n", ans[k - 1]);
	}
}

int main()
{
	while (scanf("%d%d%d%d", &n, &m, &k, &t)) {
		if (n == 0 && m == 0 && k == 0 && t == 0) break;
		static int tst = 0;
		printf("Case %d: ", ++tst);
		init();
		solve();
	}
	return 0;
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1 << 16;
vector<int> status[100000];
int ans[N];
int num[16], p[20], cnt;
bool vis[N];

bool init()
{
	for (int i = 0; i < N; ++i) {
		ans[i] = 0;
	}
	for (int i = 0; i < 100000; ++i)
		status[i].clear();
	scanf("%d", &num[0]);
	if (num[0] == 0) return false;
	for (int i = 1; i < 16; ++i)
		scanf("%d", &num[i]);
	return true;
}

bool get(int u)
{
	//if (vis[u] || vis[u ^ (N - 1)]) return false;
	cnt = 0;
	for (int i = 0; i < 16; ++i) {
		if (u & (1 << i)) {
			p[cnt++] = num[i];
		}
	}
	return (cnt == 4);
}

void solve()
{
	for (int i = 0; i < N; ++i) {
		if (get(i)) {
			sort(p, p + 4);
			do {
				int sum = p[0] * 4 + p[1] * 3 + p[2] * 2 + p[3];
				//int sum = p[per[0]] * 4 + p[per[1]] * 3 + p[per[2]] * 2 + p[per[3]];
				for (int j = 0; j < (int)status[sum].size(); ++j) {
					if ((i & status[sum][j]) == 0)
						ans[i | status[sum][j]] ++;
				}
				status[sum].push_back(i);
			} while (next_permutation(p, p + 4));
		}
	}
	long long w = 0;
	for (int i = 0; i < N; ++i) {
		w += (long long)ans[i] * (long long)ans[i ^ (N - 1)];
	}
	static int tst = 0;
	++tst;
	cout << "Case " << tst << ": ";
	cout << w / 2 << endl;
}

int main()
{
	while (true) {
		if (!init()) break;
		solve();
	}
	return 0;
}

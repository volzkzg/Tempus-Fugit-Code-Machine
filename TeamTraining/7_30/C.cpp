#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 0x7FFFFFFF/2;
const int N = 111;
const int K = 10;
struct Skill {
	int b, c, d;
	void read() {
		cin >> b >> c >> d;
	}
}skill[K];
struct Amulet {
	int a, m, now;
	vector<int> relate;
	void read() {
		relate.clear();
		now = 0;
		cin >> a >> m;
		for (int i = 1; i <= m; ++i) {
			int tmp;
			cin >> tmp;
			relate.push_back(tmp);
			now |= (1 << (tmp - 1));
		}
	}
}amulet[N];
int k, n, f[N][(1 << K)], x, y;

bool cmp(const int &a, const int &b)
{
	return a > b;
}

void init()
{
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j < (1 << k); ++j)
			f[i][j] = -INF;
	f[0][0] = 0;
	for (int i = 1; i <= k; ++i)
		skill[i].read();
	for (int i = 1; i <= n; ++i)
		amulet[i].read();
	cin >> x >> y;
}

void solve()
{
	for (int pos = 1; pos <= n; ++pos) {
		for (int i = y - 1; i >= 0; --i) {
			for (int j = 0; j < (1 << k); ++j) {
				if (f[i][j] < 0) continue;
				f[i + 1][j | amulet[pos].now] = max(f[i + 1][j | amulet[pos].now],
								    f[i][j] + amulet[pos].a);
			}
		}
	}

	vector<int> tmp;
	int sum, final_ans = 0;
	
	for (int status = 0; status < (1 << k); ++status) {
		if (f[y][status] < 0) continue;
		//cout << y << " " << status << " " << f[y][status] << endl;
		for (int full = 0; full < (1 << k); ++full) {
			int now_ans = f[y][status];
			tmp.clear();
			sum = 0;
			for (int i = 1; i <= k; ++i) {
				if (full & (1 << (i - 1))) {
					now_ans += skill[i].d;
					now_ans += skill[i].b * skill[i].c;
					//cout << "NOW_ANS " << now_ans << " " << skill[i].b << " " << skill[i].c << endl;
					if (status & (1 << (i - 1))) {
						sum += skill[i].b - 1;
					} else {
						sum += skill[i].b;
					}
				} else {
					if (status & (1 << (i - 1))) {
						now_ans += skill[i].c;
						for (int j = 2; j < skill[i].b; ++j)
							tmp.push_back(skill[i].c);
					} else {
						for (int j = 1; j < skill[i].b; ++j)
							tmp.push_back(skill[i].c);
					}
				}
			}
			if (sum > x) continue;
			//cout << status << " " << full << " " << sum << " " << now_ans << endl;
			sort(tmp.begin(), tmp.end(), cmp);

			for (int i = 0; i < min(x - sum, (int)tmp.size()); ++i) {
				now_ans += tmp[i];
			}
			final_ans = max(final_ans, now_ans);
		}
	}
	cout << final_ans << endl;
}

int main()
{
	ios::sync_with_stdio(false);
	while (cin >> k >> n) {
		init();
		solve();
	}
	return 0;
}

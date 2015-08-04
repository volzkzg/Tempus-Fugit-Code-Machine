#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const long long INF = 1e17;
long long c, tar, tmp, num_cnt;
long long num[10];
long long best_ans, ans_cnt, ans_num;
struct node {
	long long lhs, rhs;
	int oper;
	node() {}
	node(long long _lhs, long long _rhs, int _oper) {
		lhs = _lhs, rhs = _rhs, oper = _oper;
	}
	void print()
	{
		long long tmp;
		cout << lhs << " ";
		switch (oper) {
		case 1: cout << '+'; tmp = lhs + rhs; break;
		case 2: cout << '-'; tmp = lhs - rhs; break;
		case 3: cout << '*'; tmp = lhs * rhs; break;
		case 4: cout << '/'; tmp = lhs / rhs; break;
		}
		cout << " " << rhs << " = " << tmp << endl;
	}
}ans[10], state[10];

void update(long long now, int len)
{
	if (abs(now - tar) < best_ans) {
		ans_num = now;
		best_ans = abs(now - tar);
		ans_cnt = len;
		for (int i = 1; i <= len; ++i)
			ans[i] = state[i];
	}
}

void dfs(int dep)
{
	long long backup[7];
	if (num_cnt == 1) return;
	int bound = num_cnt;
	for (int i = 1; i <= bound; ++i)
		backup[i] = num[i];
	for (int i = 1; i <= bound; ++i)
		for (int j = i + 1; j <= bound; ++j) {
			long long x = backup[i];
			long long y = backup[j];
			if (x < y) swap(x, y);
			long long z;
			for (int k = 1; k <= 4; ++k) {
				z = -1;
				switch (k) {
				case 1: z = x + y; break;
				case 2: z = x - y; break;
				case 3: z = x * y; break;
				case 4: if (y != 0 && x % y == 0) z = x / y; break;
				}
				if (z <= 0) continue;
				state[dep] = node(x, y, k);
				update(z, dep);

				if (best_ans == 0) return;
				
				int tmp_num = 0;
				for (int l = 1; l <= bound; ++l)
					if (i != l && j != l)
						num[++tmp_num] = backup[l];
				num[++tmp_num] = z;
				num_cnt = tmp_num;
				
				dfs(dep + 1);
				if (best_ans == 0) return;
				
				num_cnt = bound;
			}
		}
	for (int i = 1; i <= bound; ++i)
		num[i] = backup[i];
	num_cnt = bound;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> c;
	while (c--) {
		for (int i = 1; i <= 6; ++i) 
			cin >> num[i];
		num_cnt = 6;
		ans_cnt = 0;
		best_ans = INF;
		bool flag = false;
		
		cin >> tar;
		cout << "Target: " << tar << endl;

		for (int i = 1; i <= 6; ++i)
			if (num[i] == tar) {
				flag = true;
				cout << "Best approx: " << num[i] << endl;
				break;
			} else {
				if (abs(num[i] - tar) < best_ans) {
					ans_num = num[i];
					best_ans = abs(num[i] - tar);
					ans_cnt = 0;
				}
			}
		if (!flag) {
			dfs(1);
			for (int i = 1; i <= ans_cnt; ++i) {
				ans[i].print();
			}
			cout << "Best approx: " << ans_num << endl;
		}
		cout << endl;
	}
	return 0;
}

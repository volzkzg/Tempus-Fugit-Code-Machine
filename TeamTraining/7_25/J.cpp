#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

long long n;
int r;
int tst_case;
int pri[] = {-2, -3, -5, -7, -11, -13, -17, -19, -23, -29, -31, -37, -41, -43, -47, -53, -59, -61};
vector <int> q;

long long calc(long long x) {
    if (x == 1) return 0;
    long long ret = x - 1;
    for (int i = 0; i < q.size(); ++i) {
	long long cur = (long long)pow(x + 0.5, 1.0 / abs(q[i])) - 1;
	if (q[i] < 0)
	    ret -= cur;
	else
	    ret += cur;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> tst_case;
    while (tst_case--) {
	cin >> n >> r;
	q.clear();
	for (int i = 0; i < 18; ++i) {
	    if (abs(pri[i]) > r) continue;
	    int cur = q.size();
	    for (int j = 0; j < cur; ++j) {
		if (abs(q[j] * pri[i]) <= 62)
		    q.push_back(q[j] * pri[i]);
	    }
	    q.push_back(pri[i]);
	}
	long long ans = n;
	for (;;) {
	    long long tmp = calc(ans);
	    if (tmp < n)
		ans += n - tmp;
	    else
		break;
	}
	cout << ans << endl;
    }

    return 0;
}

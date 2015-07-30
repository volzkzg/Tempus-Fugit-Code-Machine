#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

const int MAXN = 10;

double x[MAXN], y[MAXN];

double sqr(double x) {
	return x * x;
}

double dist(int i, int j) {
	return sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
}

int main() {
	ios::sync_with_stdio(false);
	while (cin >> x[1] >> y[1]) {
		for (int i = 2; i <= 4; ++i)
			cin >> x[i] >> y[i];
		double ans = 1e17;
		ans = min(ans, dist(1, 2) + dist(3, 4));
		ans = min(ans, dist(1, 3) + dist(2, 4));
		ans = min(ans, dist(1, 4) + dist(2, 3));
		cout << setiosflags(ios::fixed) << setprecision(8) << ans << endl;
	}
	return 0;
}

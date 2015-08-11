#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

long long ans;

void Update(long long &x, long long y) {
	if (x == -1)
		x = y;
	if (y == -1)
		return;
	if (x > y)
		x = y;	
}

void Solve(long long l, long long r, int dep) {
	if (dep > 11)
		return;
	if (l == 0) {
		Update(ans, r);
		return;
	}
	if(l < 0)
		return;
	if (ans != -1 && ans <= r)
		return;
	Solve((l - 1) * 2 - r, r, dep + 1);
	if (ans != -1 && ans <= r)
		return;
	Solve((l - 1) * 2 - r + 1, r, dep + 1);
	if (ans != -1 && ans <= r)
		return;
	Solve(l, r * 2 - l, dep + 1);
	if (ans != -1 && ans <= r)
		return;
	Solve(l, r * 2 + 1 - l, dep + 1);
}

int main() {
	ios::sync_with_stdio(false);
	long long l, r;
	while (cin >> l >> r) {
		ans = -1;
		Solve(l, r, 0);
		cout << ans << endl;
	}

	return 0;
}

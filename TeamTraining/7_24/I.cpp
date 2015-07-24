#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int gcd(int n, int m) {
    while (m) {
	int tmp = n % m;
	n = m;
	m = tmp;
    }
    return n;
}

int x[3], y[3];
int tst;

int Cross(int x1, int y1, int x2, int y2) {
    return abs(x1 * y2 - x2 * y1);
}

int main() {
    scanf("%d", &tst);
    for (int tt = 1; tt <= tst; ++tt) {
	for (int i = 0; i < 3; ++i)
	    scanf("%d%d", &x[i], &y[i]);
	int ans = Cross(x[0], y[0], x[2], y[2]);
        for (int i = 0; i < 2; ++i) 
	    ans = gcd(ans, Cross(x[i], y[i], x[i + 1], y[i + 1]));
	printf("Case #%d: %d\n", tt, ans);
    }
    return 0;
}

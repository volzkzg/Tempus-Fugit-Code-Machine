#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;
int n, a[N], b[N], al, bl, ar, br;

int main()
{
	ios::sync_with_stdio(false);
	while (true) {
		cin >> n;
		if (n == 0) break;
		for (int i = 1; i <= n; ++i)
			cin >> a[i];
		for (int i = 1; i <= n; ++i)
			cin >> b[i];
		sort(a + 1, a + n + 1);
		sort(b + 1, b + n + 1);
		al = bl = 1;
		ar = br = n;
		int cnt = 0;
		while (al <= ar) {
			if (a[al] > b[bl]) {
				cnt++;
				al++;
				bl++;
			} else if (a[ar] > b[br]) {
				cnt++;
				ar--;
				br--;
			} else {
				if (a[al] < b[br]) cnt--;
				al++;
				br--;
			}
		}
		cout << cnt * 200 << endl;
	}
	return 0;
}

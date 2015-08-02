#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 100 + 10;

unsigned long long a[MAXN], b[MAXN];
int len1, len2, s, t;
unsigned long long n;
bool first = true;

int main() {
	ios::sync_with_stdio(false);
	while (cin >> n >> s >> t >> len1 >> len2) {
		if (first)
			first = false;
		else
			cout << endl;
		for (int i = 1; i <= len1; ++i)
			a[i] = b[i] = 0;
		bool flag = true;
		for (int i = 1; i <= len1 - s; ++i) {
			a[i] = (unsigned long long)i;
			if (a[i] > n) {
				flag = false;
				break;
			}
		}
		while (s > 0) {
			s--;
			if (flag == false)
				break;
			for (int i = 1; i <= len1; ++i)
				b[i] = a[i];
			a[1] = 1;
			for (int i = 2; i <= len1 - s; ++i)
				if (n >= a[i - 1] && n - a[i - 1] >= b[i - 1])
					a[i] = a[i - 1] + b[i - 1];
				else {
					flag = false;
					break;
				}
		}
		if (flag == false) {
			cout << -1 << endl;
		}
		else {
			for (int i = 1; i < len1; ++i) {
				cout << a[i] << ' ';
			}
			cout << a[len1] << endl;
		}

		len1 = len2; s = t;
	        for (int i = 1; i <= len1; ++i)
			a[i] = b[i] = 0;
	        flag = true;
		for (int i = 1; i <= len1 - s; ++i) {
			a[i] = (unsigned long long)i;
			if (a[i] > n) {
				flag = false;
				break;
			}
		}
		while (s > 0) {
			s--;
			if (flag == false)
				break;
			for (int i = 1; i <= len1; ++i)
				b[i] = a[i];
			a[1] = 1;
			for (int i = 2; i <= len1 - s; ++i)
				if (n >= a[i - 1] && n - a[i - 1] >= b[i - 1])
					a[i] = a[i - 1] + b[i - 1];
				else {
					flag = false;
					break;
				}
		}
		if (flag == false) {
			cout << -1 << endl;
		}
	        else {
			for (int i = 1; i < len1; ++i) {
				cout << n - a[i] + 1 << ' ';
			}
			cout << n - a[len1] + 1 << endl;
		}

	}

	return 0;
}

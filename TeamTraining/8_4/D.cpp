#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <string>

using namespace std;

const int MAXN = 150 + 10;
const int MAXM = 11000 + 10;
const int MAXK = 20 + 5;

int f[MAXN][MAXN][MAXK];
int n, m, tst_case, pos, len;
string s, now;
char c[MAXN], a[MAXN];
int num[MAXN];

bool get_next(char &ch, int &times) 
{
	if (pos >= (int)s.size()) return false;
	ch = s[pos++];
	times = 0;
	while (pos < (int)s.size() && s[pos] >= '0' && s[pos] <= '9') {
		times = times * 10 + s[pos] - '0';
		pos++;
	}
	return true;
}

int check(char A, char B) {
	if (A > B)
		swap(A, B);
	if (A == 'A' && B == 'U')
		return 1;
	if (A == 'C' && B == 'G')
		return 2;
	return 0;
}

int dp(int l, int r, int k) {
	if (l >= r)
		return 0;
	if (f[l][r][k] != -1)
		return f[l][r][k];
	int &ret = f[l][r][k];
	ret = 0;
	for (int i = l + 1; i <= r; ++i) {
		if (check(a[l], a[i]) == 1) {
			for (int kk = 0; kk <= k; ++kk)
				ret = max(ret, dp(l + 1, i - 1, kk) + dp(i + 1, r, k - kk) + 1);
		}
		else if (check(a[l], a[i]) == 2) {
			for (int kk = 0; kk < k; ++kk)
				ret = max(ret, dp(l + 1, i - 1, kk) + dp(i + 1, r, k - kk - 1) + 1);
		}
	}
	ret = max(ret, dp(l + 1, r, k));
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> tst_case;
	for (int iCase = 1; iCase <= tst_case; ++iCase) {
		cout << "Case " << iCase << ": ";
		pos = 0;
		getline(cin, s);
		getline(cin, s);
		for (n = 1; get_next(c[n], num[n]); n++);
		--n;
		cin >> m;
		for (int i = 1; i <= 150; ++i)
			a[i] = 0;
		len = 0;
		int ans = 0;
		if (check(c[1], c[n]) == 1) {
			int tmp = min(num[1], num[n]);
			num[1] -= tmp;
			num[n] -= tmp;
			ans += tmp;
		}
		else if (check(c[1], c[n]) == 2) {
			int tmp = min(num[1], num[n]);
			tmp = min(tmp, m);
			num[1] -= tmp;
			num[n] -= tmp;
			m -= tmp;
			ans += tmp;
		}
		for (int i = 1; i <= min(num[1], 50); ++i)
			a[++len] = c[1];
		for (int i = 2; i < n; ++i)
			for (int j = 1; j <= num[i]; ++j)
				a[++len] = c[i];
		for (int i = 1; i <= min(num[n], 50); ++i)
			a[++len] = c[n];
		for (int i = 1; i <= len; ++i)
			for (int j = 1; j <= len; ++j)
				for (int k = 0; k <= m; ++k)
					f[i][j][k] = -1;
		ans += dp(1, len, m);
		cout << ans << endl;
	}
	
	return 0;
}


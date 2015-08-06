#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 55555;
int n, w[N], h[N], pre[N];

template<class T>
class ST
{
public:
	T f[21][N];
	int LOG[N];
	int lowbit(int x)
	{
		return (x & (-x));
	}
	
	void init(T *a, int len)
	{
		LOG[1] = 0;
		for(int i = 2; i < N; ++i) {
			LOG[i] = LOG[i - 1] + (lowbit(i) == i);
		}
		for(int i = 0; i < len; ++i)
			f[0][i] = a[i + 1];
		for(int i = 1; (1 << i) <= len; ++i)
			for(int j = 0; j + (1 << i) - 1 < len; ++j) {
				f[i][j] = min(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
			}
	}
	T query(int l, int r)
	{
		l--, r--;
		int L = (r - l) + 1;
		int LG = LOG[L];
		return min(f[LG][l], f[LG][r - (1 << LG) + 1]);
	}
	
};

int main()
{
	ios::sync_with_stdio(false);
	ST<int> data;
	while (cin >> n) {
		if (n == -1) break;

		int ans = 0;
		pre[0] = 0;
		for (int i = 1; i <= n; ++i) {
			cin >> w[i] >> h[i];
			pre[i] = pre[i - 1] + w[i];
		}
		
		data.init(h, n);
		for (int i = 1; i <= n; ++i) {
			int l, r, lans, rans;
			lans = i, rans = i;
			
			l = i + 1, r = n;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (data.query(i, mid) >= h[i]) {
					rans = mid;
					l = mid + 1;
				} else {
					r = mid - 1;
				}
			}

			l = 1, r = i - 1;
			while (l <= r){
				int mid = (l + r) >> 1;
				if (data.query(mid, i) >= h[i]) {
					lans = mid;
					r = mid - 1;
				} else {
					l = mid + 1;
				}
			}
			ans = max(ans, (pre[rans] - pre[lans - 1]) * h[i]);
		}
		cout << ans << endl;
	}
	return 0;
}

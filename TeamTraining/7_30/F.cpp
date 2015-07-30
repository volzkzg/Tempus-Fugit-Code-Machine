#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 100000 + 10;
pair<int, pair<int, int> > course[N];
vector<int> arr[N];
int n;

int main()
{
	ios::sync_with_stdio(false);
	while (cin >> n) {
		for (int i = 1; i <= n; ++i) {
			cin >> course[i].first >> course[i].second.first;
			course[i].second.second = i;
		}
		sort(course + 1, course + 1 + n);
		int ans = 0;
		int right_most = -1;
		for (int i = 1; i <= n; ++i) {
			if (course[i].first >= right_most) {
				ans++;
				arr[ans].clear();
				right_most = course[i].second.first;
				arr[ans].push_back(course[i].second.second);
			} else {
				right_most = min(right_most, course[i].second.first);
				arr[ans].push_back(course[i].second.second);
			}
		}
		cout << ans << endl;
		for (int i = 1; i <= ans; ++i) {
			cout << arr[i][0];
			for (int j = 1; j < (int)arr[i].size(); ++j)
				cout << " " << arr[i][j];
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}

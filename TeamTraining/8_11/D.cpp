#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const int N = 100;
string s[N];
struct Node {
	bool red, blue;
	Node() {}
	Node(bool _red, bool _blue) {
		red = _red, blue = _blue;
	}
	Node(char c) {
		if (c == 'R') {
			red = true;
			blue = false;
		} else if (c == 'B') {
			red = false;
			blue = true;
		} else if (c == 'G') {
			red = true;
			blue = true;
		} else {
			red = false;
			blue = false;
		}
	}
}state[N][N];
int T, n, m;
int dx[2] = {1, 1};
int dy[2] = {1, -1};

bool bound(int x, int y)
{
	if (x >= 1 && x <= n && y >= 1 && y <= m) return true;
	else return false;
}

void doing(int x, int y, int mode)
{
	/*
	cout << x << " " << y << " ";
	if (mode) cout << "BLUE" << endl;
	else cout << "RED" << endl;
	*/
	while (bound(x, y)) {
		if (mode == 0) {
			if (state[x][y].red)
				state[x][y].red = false;
			else
				break;
		}
		if (mode == 1) {
			if (state[x][y].blue)
				state[x][y].blue = false;
			else
				break;
		}
		x += dx[mode];
		y += dy[mode];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> s[i];
		m = s[0].size();
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				state[i][j] = Node(s[i - 1][j - 1]);
			}
		}
		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (state[i][j].red) {
					doing(i, j, 0);
					cnt++;
				}
				if (state[i][j].blue) {
					doing(i, j, 1);
					cnt++;
				}
			}
		}
		cout << cnt << endl;
	}
	return 0;
	
}

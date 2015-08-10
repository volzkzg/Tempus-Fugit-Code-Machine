#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int N = 1 << 20;
int f[30000][3], mark[11][N + 10];
int cnt, m;
struct Node {
	int pos, state;
	Node(){}
	Node(int _pos, int _state) {
		pos = _pos;
		state = _state;
	}
} p[N];
queue<pair<int, int> > q;

int get_num(int u, int v)
{
	if (mark[u][v] == 0) {
		mark[u][v] = ++cnt;
		q.push(make_pair(u, v));
	}
	return mark[u][v];
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> m;
	q.push(make_pair(0, 0));
	mark[0][0] = 1;
	cnt = 1;
	while (!q.empty()) {
		int pos = q.front().first;
		int state = q.front().second;
		q.pop();
		int num = mark[pos][state];
		int next_state;
		int next_pos;
		int next_num;
		
		if ((state & (1 << pos)) == 0) {
			// doing horizontal 
			next_state = (state | ((1 << pos) + (1 << (pos + m))));
			next_pos = pos + 1;
			if (next_pos >= m) {
				next_pos -= m;
				next_state >>= m;
			}
			next_num = get_num(next_pos, next_state);
			f[num][0] = next_num;


			// doing vertical
			if (pos + 1 == m) {
				f[num][1] = -1;
			} else {
				next_state = (state | ((1 << pos) + (1 << (pos + 1))));
				next_pos = pos + 1;
				next_num = get_num(next_pos, next_state);
				f[num][1] = next_num;
			}

			// doing nothing
			f[num][2] = -1;
		} else {
			// doing horizontal or vertial
			f[num][0] = f[num][1] = -1;
			
			// doing nothing
			next_state = state;
			next_pos = pos + 1;
			if (next_pos >= m) {
				next_pos -= m;
				next_state >>= m;
			}
			next_num = get_num(next_pos, next_state);
			f[num][2] = next_num;
		}
	}

	cout << cnt + 1 << " " << 1 << endl;
	cout << 1 << " " << 1 << endl;
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < (1 << (2 * m)); ++j) {
			if (mark[i][j] > 0) {
				p[mark[i][j]] = Node(i, j);
			}
		}
	for (int i = 1; i <= cnt; ++i) {
		int pos = p[i].pos;
		int state = p[i].state;
		int num = mark[pos][state];
		for (int i = 0; i < 3; ++i) {
			if (f[num][i] == -1)
				cout << cnt + 1;
			else 
				cout << f[num][i];
			if (i == 2) cout << endl;
			else cout << " ";
		}
	}
	cout << cnt + 1 << " " << cnt + 1 << " " << cnt + 1 << endl;
	return 0;
}

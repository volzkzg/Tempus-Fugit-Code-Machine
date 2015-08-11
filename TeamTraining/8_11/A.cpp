#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;
const long long INF = 1LL<<60;
struct Node {
	long long LL, LR, RL, RR;
	Node() {}
	Node(long long _LL, long long _LR, long long _RL, long long _RR) {
		LL = _LL, LR = _LR, RL = _RL, RR = _RR;
	}
	void clear() {
		LL = LR = RL = RR = -INF;
	}
};

Node tree[N << 2];
int T, n, m;
long long num[N];

long long max(long long a, long long b, long long c, long long d, long long e)
{
	return (max(a, max(b, max(c, max(d, e)))));
}

void push_up(int l, int r, int mid, int rt)
{
	int lc = rt << 1;
	int rc = rt << 1 | 1;
	tree[rt].LL = max(-INF, tree[lc].LL, tree[rc].LL,
			  tree[lc].LR + tree[rc].LL, tree[lc].LL + tree[rc].RL);
	tree[rt].LR = max(-INF, tree[lc].LR, tree[rc].LR,
			  tree[lc].LL + tree[rc].RR, tree[lc].LR + tree[rc].LR);
	tree[rt].RL = max(-INF, tree[lc].RL, tree[rc].RL,
			  tree[lc].RR + tree[rc].LL, tree[lc].RL + tree[rc].RL);
	tree[rt].RR = max(-INF, tree[lc].RR, tree[rc].RR,
			  tree[lc].RL + tree[rc].RR, tree[lc].RR + tree[rc].LR);
}

void build(int l, int r, int rt)
{
	tree[rt].clear();
	if (l == r) {
		if (l & 1) {
			tree[rt].LL = num[l];
		} else {
			tree[rt].RR = num[l];
		}
	} else {
		int mid = (l + r) >> 1;
		build(l, mid, rt << 1);
		build(mid + 1, r, rt << 1 | 1);
		push_up(l, r, mid, rt);
	}
}

void max(Node &u, const Node &v)
{
	u.LL = max(u.LL, v.LL);
	u.LR = max(u.LR, v.LR);
	u.RL = max(u.RL, v.RL);
	u.RR = max(u.RR, v.RR);
}

Node qry(int l, int r, int rt, int a, int b)
{
	Node ret = Node(-INF, -INF, -INF, -INF);
	if (a <= l && r <= b) {
		max(ret, tree[rt]);
		return ret;
	} else {
		int lc = rt << 1;
		int rc = rt << 1 | 1;
		int mid = (l + r) >> 1;
		Node lhs, rhs;
		if (a <= mid) 
			lhs = qry(l, mid, lc, a, b);
		else
			lhs = Node(-INF, -INF, -INF, -INF);
		if (b > mid) 
			rhs = qry(mid + 1, r, rc, a, b);
		else
			rhs = Node(-INF, -INF, -INF, -INF);
		max(ret, lhs);
		max(ret, rhs);
		ret.LL = max(ret.LL, max(lhs.LL + rhs.RL, lhs.LR + rhs.LL));
		ret.LR = max(ret.LR, max(lhs.LL + rhs.RR, lhs.LR + rhs.LR));
		ret.RL = max(ret.RL, max(lhs.RL + rhs.RL, lhs.RR + rhs.LL));
		ret.RR = max(ret.RR, max(lhs.RL + rhs.RR, lhs.RR + rhs.LR));
		return ret;
	}
}

void upd(int l, int r, int rt, int a, int b)
{
	if (l == r) {
		if (l & 1) {
			tree[rt].LL = num[l];
		} else {
			tree[rt].RR = num[l];
		}	
	} else {
		int mid = (l + r) >> 1;
		if (a <= mid)
			upd(l, mid, rt << 1, a, b);
		else 
			upd(mid + 1, r, rt << 1 | 1, a, b);
		push_up(l, r, mid, rt);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 1; i <= n; ++i)
			cin >> num[i];
		build(1, n, 1);
		for (int i = 1; i <= m; ++i) {
			int mode, a, b;
			cin >> mode >> a >> b;
			//cout << mode << " " << a << " " << b << endl;
			if (mode == 0) {
				Node ans = qry(1, n, 1, a, b);
				cout << max(ans.LL, ans.LR, ans.RL, ans.RR, -INF) << endl;
			} else {
				num[a] = b;
				upd(1, n, 1, a, b);
			}
		}
	}
	return 0;
}

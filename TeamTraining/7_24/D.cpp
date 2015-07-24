#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const long long INF = 1e16;
const long long N = 200000 + 10;

long long sign(long long x) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

struct point {
	long long x, y, id;
	point(): x(0), y(0) {}
	point(const long long &x, const long long &y): x(x), y(y) {}
	point operator + (const point &rhs) const { return point(x + rhs.x, y + rhs.y); }
	point operator - (const point &rhs) const { return point(x - rhs.x, y - rhs.y); }
	double len() const { return hypot(x, y); }
	double norm() const { return x * x + y * y; }
	point unit() const { double k = len(); return point(x / k, y / k); }
	point rot(const double &a) const { return point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
	friend long long dot(const point &a, const point &b) { return a.x * b.x + a.y * b.y; }
	friend long long det(const point &a, const point &b) { return a.x * b.y - a.y * b.x; }
	friend long long dist(const point &a, const point &b, const point &c) { // dist from C to AB
		return fabs(det(a - c, b - c) / (a - b).len());
	}
};

bool onSeg(const point &a, const point &b, const point &c) { // C is not strict on AB
	return sign(dot(a - c, b - c)) <= 0 && sign(det(b - a, c - a)) == 0;
}

inline long long sqr(const long long &x) {
	return x * x;
}

inline long long dist(const point &a, const point &b) {
	return sqr(a.x - b.x) + sqr(a.y - b.y);
}

struct rectangle {
	long long lx, rx, ly, ry;
	inline void set(const point &p) {
		lx = rx = p.x;
		ly = ry = p.y;
	}
	inline void mergy(const point &p) {
		lx = min(lx, p.x);
		rx = max(rx, p.x);
		ly = min(ly, p.y);
		ry = max(ry, p.y);
	}
	inline void mergy(const rectangle &r) {
		lx = min(lx, r.lx);
		rx = max(rx, r.rx);
		ly = min(ly, r.ly);
		ry = max(ry, r.ry);
	}
	/*	minimum distance	*/
	inline long long dist(const point &p) {
		if (p.x <= lx && p.y <= ly) {
			return sqr(p.x - lx) + sqr(p.y - ly);
		}
		if (p.x <= rx && p.y <= ly) {
			return sqr(p.y - ly);
		}
		if (p.x >= rx && p.y <= ly) {
			return sqr(p.x - rx) + sqr(p.y - ly);
		}
		if (p.x >= rx && p.y <= ry) {
			return sqr(p.x - rx);
		}
		if (p.x >= rx && p.y >= ry) {
			return sqr(p.x - rx) + sqr(p.y - ry);
		}
		if (p.x >= lx && p.y >= ry) {
			return sqr(p.y - ry);
		}
		if (p.x <= lx && p.y >= ry) {
			return sqr(p.x - lx) + sqr(p.y - ry);
		}
		if (p.x <= lx && p.y >= ly) {
			return sqr(p.x - lx);
		}
		return 0;
	}
};

struct node {
	long long child[2];
	point p;
	rectangle r;
	inline void set(const point &_p) {
		p = _p;
		r.set(p);
		child[0] = child[1] = 0;
	}
};

long long size, cnt;
point a[N], b[N];
node tree[N];

inline bool xcompare(const point &a, const point &b) {
	return a.x < b.x || a.x == b.x && a.y < b.y;
}

inline bool ycompare(const point &a, const point &b) {
	return a.y < b.y || a.y == b.y && a.x < b.x;
}

inline long long build(long long left, long long right, bool dim = 0) {
	long long x = ++size, mid = left + right >> 1;
	nth_element(a + left, a + mid, a + right, dim ? xcompare : ycompare);
	tree[x].set(a[mid]);
	if (left < mid) {
		tree[x].child[0] = build(left, mid, dim ^ 1);
		tree[x].r.mergy(tree[tree[x].child[0]].r);
	}
	if (mid + 1 < right) {
		tree[x].child[1] = build(mid + 1, right, dim ^ 1);
		tree[x].r.mergy(tree[tree[x].child[1]].r);
	}
	return x;
}

inline long long insert(long long x, const point &p, bool dim = 0) {
	if (x == 0) {
		tree[++size].set(p);
		return size;
	}
	tree[x].r.mergy(p);
	if (dim && xcompare(p, tree[x].p) || !dim && ycompare(p, tree[x].p)) {
		tree[x].child[0] = insert(tree[x].child[0], p, dim ^ 1);
	} else {
		tree[x].child[1] = insert(tree[x].child[1], p, dim ^ 1);
	}
	return x;
}
	
/*	query kth-minimum	*/
inline void query(long long x, const point &p, long long k, pair<long long, int> ret[], bool dim = 0) {
	if (tree[x].r.dist(p) > ret[k].first) {
		return;
	}
	pair<long long, int> val = make_pair(dist(tree[x].p, p), tree[x].p.id);

	for (long long i = 1; i <= k; ++i) {
		if (val < ret[i]) {
			for (long long j = k + 1; j > i; --j) {
				ret[j] = ret[j - 1];
			}
			ret[i] = val;
			break;
		}
	}
	if (dim && xcompare(p, tree[x].p) || !dim && ycompare(p, tree[x].p)) {
		if (tree[x].child[0]) {
			query(tree[x].child[0], p, k, ret, dim ^ 1);
		}
		if (tree[x].child[1]) {
			query(tree[x].child[1], p, k, ret, dim ^ 1);
		}
	} else {
		if (tree[x].child[1]) {
			query(tree[x].child[1], p, k, ret, dim ^ 1);
		}
		if (tree[x].child[0]) {
			query(tree[x].child[0], p, k, ret, dim ^ 1);
		}
	}
}

pair<long long, int> ans[10];

inline void clear() {
	size = 0;
}

struct Polygon { // stored in [0, n)
	long long n; point ps[N];
	bool contain(const point &p) const { // 1 if on border or inner, 0 if outter
		static point A, B; long long res = 0;
		for (long long i = 0; i < n; ++i) {
			A = ps[i]; B = ps[(i + 1) % n];
			if (onSeg(A, B, p)) return 1;
			if (sign(A.y - B.y) <= 0) swap(A, B);
			if (sign(p.y - A.y) > 0) continue;
			if (sign(p.y - B.y) <= 0) continue;
			res += (int)(sign(det(B - p, A - p)) > 0);
		} return res & 1;
	}
}poly;


int main()
{
	ios::sync_with_stdio(false);
	long long T, tst = 0, n, R, B, M;
	for (cin >> T; T; T--) {
		cout << "Case #" << ++tst << ":" << endl;
		cin >> n;
		for (long long i = 0; i < n; ++i) {
			cin >> b[i].x >> b[i].y;
			b[i].id = i + 1;
		}
		cin >> R;
		for (long long i = 1; i <= R; ++i) {
			cout << "Region " << i << endl;
			clear();
			poly.n = 0;
			cin >> poly.n;
			for (long long j = 0; j < poly.n; ++j) 
				cin >> poly.ps[j].x >> poly.ps[j].y;
			cnt = 0;
			for (long long j = 0; j < n; ++j)
				if (poly.contain(b[j]))
					a[cnt++] = b[j];
			//cout << cnt << endl;
			long long root = build(0, cnt);
			cin >> M;
			for (long long j = 0; j < M; ++j) {
				ans[1].first = ans[2].first = INF;
				point tmp;
				cin >> tmp.x >> tmp.y;
				query(root, tmp, 2, ans, 0);
				cout << ans[1].second << " " << ans[2].second << endl;
			}
		}
	}
	return 0;
}

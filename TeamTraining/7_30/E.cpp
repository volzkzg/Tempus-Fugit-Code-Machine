#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

const double eps = 1e-8;
const int N = 30;

int sign(double x)
{
	if (x > eps) return 1;
	if (x < -eps) return -1;
	return 0;
}

struct Point {
	double x, y;
	Point() {}
	Point(double _x, double _y):x(_x), y(_y) {}

	Point operator - (const Point &rhs) const {
		Point tmp = Point(x - rhs.x, y - rhs.y);
		return tmp;
	}

	bool onSeg(const Point &a, const Point &b) const {
		const Point &c = *this;
		return ((sign(dot(a - c, b - c)) <= 0) &&
			(sign(det(b - a, c - a)) == 0));
	}

	friend double dot(const Point &a, const Point &b) {
		return (a.x * b.x + a.y * b.y);
	}
	friend double det(const Point &a, const Point &b) {
		return (a.x * b.y - a.y * b.x);
	}
	void read() {
		cin >> x >> y;
	}
};
struct Polygon {
	int n;
	Point ps[N];

	bool contain(const Point &p) const {
		static Point A,B;
		int res = 0;
		for (int i = 0; i < n; ++i) {
			A = ps[i];
			B = ps[(i + 1) % n];
			if (p.onSeg(A, B)) return 1;
			if (sign(A.y - B.y) <= 0) swap(A, B);
			if (sign(p.y - A.y) > 0) continue;
			if (sign(p.y - B.y) <= 0) continue;
			res += (int)(sign(det(B - p, A - p)) > 0);
		}
		return res & 1;
	}
}poly;

double P0, Q0, P1, Q1;
int n, A, B;

int main()
{
	//bool flag = false;
	ios::sync_with_stdio(false);
	while (cin >> P0 >> Q0 >> P1 >> Q1) {
		//if (flag) cout << endl;
		//else flag = true;
		cin >> poly.n >> A >> B;
		double ans = 0;
		for (int i = 0; i < poly.n; ++i)
			poly.ps[i].read();
		for (int i = ceil(P0); i <= floor(P1); ++i)
			for (int j = ceil(Q0); j <= floor(Q1); ++j) {
				double x, y;
				x = i, y = j;
				Point now = Point(x, y);
				if (poly.contain(now)) {
					double x1, x2, y1, y2;
					x1 = x - 0.5;
					x2 = x + 0.5;
					y1 = y - 0.5;
					y2 = y + 0.5;
					x1 = max(x1, P0);
					x2 = min(x2, P1);
					y1 = max(y1, Q0);
					y2 = min(y2, Q1);
					ans += (x2 - x1) * (y2 - y1) * (A * x + B * y);
				}
			}
		cout << setiosflags(ios::fixed) << setprecision(3) << ans / ((P1 - P0) * (Q1 - Q0)) << endl;
	}
	return 0;
}


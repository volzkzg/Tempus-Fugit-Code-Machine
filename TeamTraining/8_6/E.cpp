#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 333;
const double eps = 1e-8;
int sign(const double &a) {
	if (a < -eps) return -1;
	if (a > eps) return 1;
	return 0;
}

struct Point {
	double x, y;
	Point() {}
	Point(double _x, double _y) {
		x = _x, y = _y;
	}
	void read() {
		cin >> x >> y;
	}
	Point operator + (const Point &rhs) const {return Point(x + rhs.x, y + rhs.y); }
	Point operator - (const Point &rhs) const {return Point(x - rhs.x, y - rhs.y); }
	Point operator * (const double &k) const {return Point(x * k, y * k); }
	Point operator / (const double &k) const {return Point(x / k, y / k); }
	friend double dot(const Point &a, const Point &b) {return a.x * b.x + a.y * b.y; }
	friend double det(const Point &a, const Point &b) {return a.x * b.y - a.y * b.x; }
	bool onSeg(const Point &a, const Point &b) const {
		const Point &c = *this;
		return (sign(dot(a - c, b - c)) <= 0 &&
			sign(det(b - a, c - a)) == 0);
			
	}
	bool operator == (const Point &rhs) const {
		if (sign(x - rhs.x) == 0 &&
		    sign(y - rhs.y) == 0) return true;
		return false;
	}
	bool operator < (const Point &rhs) const {
		if (sign(x - rhs.x) == 0)
			return (sign(y - rhs.y) < 0);
		return (sign(x - rhs.x) < 0);
	}
	void print()
	{
		cout << x << " " << y << endl;
	}
}p[N];
vector<Point> vec;
int n;

bool segIntersect(const Point &a, const Point &b, const Point &c, const Point &d, Point &e)
{
	double s1 = det(c - a, d - a);
	double s2 = det(d - b, c - b);
	if (!sign(s1 + s2)) return false;
	e = ((b - a) * (s1 / (s1 + s2))) + a;
	return e.onSeg(a, b) && e.onSeg(c, d);
}

bool cmp(const Point &a, const Point &b) {
	if (a.x == b.x) return (a.y < b.y);
	return (a.x < b.x);
}

int main()
{
	ios::sync_with_stdio(false);
	while (cin >> n) {
		if (n == 0) break;
		static int tst_case = 0;
		vec.clear();
		for (int i = 1; i <= n; ++i) {
			p[i].read();
			if (i != n) vec.push_back(p[i]);
		}
		for (int i = 1; i < n; ++i)
			for (int j = i + 1; j < n; ++j) {
				Point inter;
				bool res = segIntersect(p[i], p[i + 1], p[j], p[j + 1], inter);
				if (res) {
					vec.push_back(inter);
				}
			}
		sort(vec.begin(), vec.end());
		vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
		int V = vec.size();
		int E = n - 1;
		for (int i = 0; i < V; ++i) {
			for (int j = 1; j < n; ++j) {
				if ((vec[i] == p[j]) || (vec[i] == p[j + 1])) continue;
				if (vec[i].onSeg(p[j], p[j + 1])) {
					//cout << "YES" << endl;
					E++;
				}
			}
		}
		cout << "Case " << ++tst_case << ": There are " << 2 + E - V << " pieces." << endl;
	}
	return 0;
}

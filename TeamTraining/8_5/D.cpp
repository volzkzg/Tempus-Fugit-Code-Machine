#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

const long double pi = acos(-1.0);
const long double eps = 1e-6;
const int N = 55;

long double rand01()
{
	return rand() / (double)RAND_MAX;
}

long double rand_eps()
{
	return (rand01() - 0.5) * eps;
}

struct Point {
	long double x, y, z;
	Point() {}
	Point(long double _x, long double _y, long double _z) {
		x = _x, y = _y, z = _z;
	}
	Point operator - (Point &rhs) const {
		Point ret(x - rhs.x, y - rhs.y, z - rhs.z);
		return ret;
	}
	void read() {
		cin >> x >> y >> z;
		x += rand_eps();
		y += rand_eps();
		z += rand_eps();
	}
}p[N];
int n;

Point cross(Point a, Point b)
{
	return Point(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

long double dot(Point a, Point b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

long double hyper(Point &a, Point &b, Point &c, Point &o)
{
	return dot(cross(b - a, c - a), o - a);
}

long double length(Point a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

long double area(Point a, Point b, Point c)
{
	return length(cross(b - a, c - a));
}

int main() {
	ios::sync_with_stdio(false);
	srand(time(NULL));

	cin >> n;
	long double final_ans = 0;
	for (int i = 1; i <= n; ++i) 
		p[i].read();
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j)
			for (int k = j + 1; k <= n; ++k) {
				int cnt = 0, sum = 0;
				bool flag = true;
				for (int now = 1; now <= n; ++now) {
					if (now == i || now == j || now == k) continue;
					//cout << i << " " << j << " " << k << " " << now << endl;
					long double ans = hyper(p[i], p[j], p[k], p[now]);
					cnt++;
					if (ans > 0) sum++;
					else if (ans < 0) sum--;
					if (abs(sum) != cnt) {
						flag = false;
						break;
					}
				}
				if (flag) {
					final_ans += area(p[i], p[j], p[k]);
					//cout << final_ans << endl;
				}
			}
	cout << setiosflags(ios::fixed) << setprecision(10) << final_ans / 2.0 << endl;
	return 0;
}

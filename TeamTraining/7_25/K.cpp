#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

int m, n, p, q;

struct Plane {
	int a, b, c, d;
	void read() {
		scanf("%d%d%d%d", &a, &b, &c, &d);
	}
}plane[110];
struct Sphere {
	int x, y, z, r;
	void read() {
		scanf("%d%d%d%d", &x, &y, &z, &r);
	}
}sphere[20];
struct Point {
	int x, y, z;
	void read() {
		scanf("%d%d%d", &x, &y, &z);
	}
} A[210], B[2010];

__inline long long sqr(long long w)
{
	return w * w;
}

inline long long calc_plane(const Point &u, const Plane &v)
{
	return ((long long)v.a * u.x + (long long)v.b * u.y +
		(long long)v.c * u.z + v.d);
}

inline int calc_sphere(const Point &u, const Sphere &v)
{
	long long w = sqr(u.x - v.x) + sqr(u.y - v.y) + sqr(u.z - v.z);
	if (w < sqr(v.r)) return 1;
	else return -1;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d", &m, &n, &p, &q);
		for (int i = 1; i <= m; ++i)
			plane[i].read();
		for (int i = 1; i <= n; ++i) 
			sphere[i].read();
		for (int i = 1; i <= p; ++i)
			A[i].read();
		for (int i = 1; i <= q; ++i)
			B[i].read();
		bool flag = true;
		int ans = 1;
		for (int i = 1; i <= p; ++i) {
			int tmp = 1;
			for (int k = 1; k <= m; ++k) {
				long long calc;
				calc = calc_plane(A[i], plane[k]);
				calc /= abs(calc);
				if (calc < 0) calc = 0;
				tmp ^= calc;
			}
			for (int k = 1; k <= n; ++k) {
				int calc;
				calc = calc_sphere(A[i], sphere[k]);
				if (calc < 0) calc = 0;
				tmp ^= calc;
			}
			if (i == 1) ans = tmp;
			if (i != 1 && ans != tmp) {
				flag = false;
				goto out;
			}
		}
	out:;
		if (flag) {
			for (int i = 1; i <= q; ++i) {
				int status = 2;
				if (p > 0) {
					int cnt = 0;
					for (int k = 1; k <= m; ++k) {
						long long calc1, calc2;
						calc1 = calc_plane(A[1], plane[k]);
						calc2 = calc_plane(B[i], plane[k]);
						calc1 /= abs(calc1);
						calc2 /= abs(calc2);
						if (calc1 * calc2 < 0)
							cnt++;
					}
					for (int k = 1; k <= n; ++k) {
						int calc1, calc2;
						calc1 = calc_sphere(A[1], sphere[k]);
						calc2 = calc_sphere(B[i], sphere[k]);
						if (calc1 * calc2 < 0)
							cnt++;
					}
					if (cnt & 1) {
						status = 1;
					} else {
						status = 0;
					}
				}
				switch (status) {
				case 2:printf("Both\n"); break;
				case 1:printf("R\n"); break;
				case 0:printf("Y\n"); break;
				}
			}
		
		} else {
			printf("Impossible\n");
		}
		if (T != 0) puts("");
	}
	return 0;
}

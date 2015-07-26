#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const double INF = 1e10;
const double eps = 1e-8;

double ax, bx, cx, ay, by, cy;
double Lx, Ly, Rx, Ry;

double dist(double x, double y, double xx, double yy) {
	return sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
}

double calc(double x, double y) {
	double dist1 = dist(ax, ay, x, y);
	double dist2 = dist(bx, by, x, y);
	double dist3 = dist(cx, cy, x, y);
	double maxd = -INF;
	maxd = max(maxd, dist1);
	maxd = max(maxd, dist2);
	maxd = max(maxd, dist3);
	return dist1 * 2 + dist2 * 2 + dist3 * 2 - maxd;
}

double check(double x) {
	Ly = -INF; Ry = INF;
	while (Ry - Ly > eps) {
		cerr << Ly << ' ' << Ry << endl;
		double mid1 = (Ly * 2 + Ry) / 3;
		double mid2 = (Ry * 2 + Ly) / 3;
		if (calc(x, mid1) > calc(x, mid2)) 
			Ly = mid1;
		else 
			Ry = mid2;
		
	}
	return calc(x, Ly);
}

int main() {
	ios::sync_with_stdio(false);
	for (;;) {
		if (ax < 0 && ay < 0 && bx < 0 && by < 0 && cx < 0 && cy < 0) {
			break;
		}
	        Lx = -INF, Ly = -INF, Rx = INF, Ry = INF;
		while (Rx - Lx > eps) {
			cerr << Lx << ' ' << Rx << endl;
			double mid1 = (Lx * 2 + Rx) / 3;
			double mid2 = (Rx * 2 + Lx) / 3;
			if (check(mid1) > check(mid2))
				Lx = mid1;
			else
				Rx = mid2;
		}
		printf("%.8lf\n", check(Ly));
	}

	return 0;
}

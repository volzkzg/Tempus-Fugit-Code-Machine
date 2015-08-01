#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) {
    return Vector(A.x + B.x, A.y + B.y);
}

Vector operator - (Point A, Point B) {
    return Vector(A.x - B.x, A.y - B.y);
}

Vector operator / (Point A, double d) {
    return Vector(A.x / d, A.y / d);
}

const double eps = 1e-10;

int dcmp(double x) {
    if (fabs(x) < eps)
	return 0;
    else
	return x < 0 ? -1 : 1;
}

bool operator == (const Point& a, const Point &b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}

double Dot(Vector A, Vector B) {
    return A.x * B.x + A.y * B.y;
}

double Length(Vector A) {
    return sqrt(Dot(A, A));
}

double angle(Vector v) {
    return atan2(v.y, v.x);
}

struct Circle {
    Point c;
    double r;
    Circle (Point c, double r) : c(c), r(r) {}
    Point point(double a) {
	return Point(c.x + cos(a) * r, c.y + sin(a) * r);
    }
};

void c2point(Circle c1,Circle c2,Point &rp1,Point &rp2){
    if (c1.c == c2.c && dcmp(c1.r - c2.r) == 0) {
        rp1 = c1.c + Point(0, c1.r);
        rp2 = c1.c - Point(0, c1.r);
        return;
    }
    Point p1 = c1.c, p2 = c2.c;
    double r1 = c1.r, r2 = c2.r;
    double a = p2.x - p1.x, b = p2.y - p1.y;
    double r = (a * a + b * b + r1 * r1 - r2 * r2) / 2;
    double tmp;
    if (a == 0 && b != 0) {
        rp1.y = rp2.y = r / b;
        tmp = r1 * r1 - rp1.y * rp1.y;
        if (dcmp(tmp) <= 0) tmp = 0;
        rp1.x = sqrt(tmp);
        rp2.x = -rp1.x;
    }
    else if (a != 0 && b == 0) {
        rp1.x = rp2.x = r / a;
        tmp = r1 * r1 - rp1.x * rp1.x;
        if (dcmp(tmp) <= 0) tmp = 0;
        rp1.y = sqrt(tmp);
        rp2.y = -rp1.y;
    }
    else if (a != 0 && b != 0) {
        tmp = b * b * r * r - (a * a + b * b) * (r * r - r1 * r1 * a * a);
        if (dcmp(tmp) <= 0) tmp = 0;
        rp1.y = (b * r + sqrt(tmp)) / (a * a + b * b);
        rp2.y = (b * r - sqrt(tmp)) / (a * a + b * b);
        rp1.x = (r - b * rp1.y) / a;
        rp2.x = (r - b * rp2.y) / a;
    }
}

Point A, B, C, D, E, F, G, H;
double AB, BC, CD, DA, EF;

int main() {
    int tst_case, cur;
    scanf("%d", &tst_case);
    for (int tt = 1; tt <= tst_case; ++tt) {
        scanf("%lf%lf%lf%lf%lf", &AB, &BC, &CD, &DA, &EF);
	C = Point(0.0, 0.0);
	B = Point(BC, 0.0);
	Circle cir1(C, DA);
	Circle cir2(B, 2 * EF);
	Point p;
	c2point(cir1, cir2, H, p);
	G = H + (B - C);
	cir1 = Circle(C, CD);
	cir2 = Circle(G, AB);
	c2point(cir1, cir2, D, p);
	A = D + (C - H);
	printf("Case #%d:\n", tt);
	printf("%.6lf %.6lf\n", A.x, A.y);
	printf("%.6lf %.6lf\n", B.x, B.y);
	printf("%.6lf %.6lf\n", C.x, C.y);
	printf("%.6lf %.6lf\n", D.x, D.y);
    }
    
    return 0;
}

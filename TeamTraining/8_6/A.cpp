#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;
struct Point {
        int x, y, r;
        double rad;
        Point() {}
        Point(int _x, int _y, int _r) {
                x = _x, y = _y, r = _r;
        }
        void read() {
                cin >> x >> y >> r;
        }
        void print()
        {
                cout << x << " " << y << " " << r << endl;
        }
        friend void reverse(Point &hs) {
                hs.x *= -1;
                hs.y *= -1;
                hs.r ^= 1;
        }
        Point operator - (const Point &rhs) const {
                return Point(x - rhs.x, y - rhs.y, r);
        }
        bool operator < (const Point &rhs) const {
                return (rad < rhs.rad);
        }
}p[N], q[N];
int n, cnt;

int next(int x)
{
        return (x % cnt) + 1;
}

double cross(const Point &a, const Point &b)
{
        return a.x * b.y - a.y * b.x;
}

int main()
{
        ios::sync_with_stdio(false);
        while (cin >> n) {
                if (n == 0) break;
                for (int i = 1; i <= n; ++i)
                        p[i].read();
                if (n <= 3) {
                        cout << n << endl;
                        continue;
                }
                /*
                cout << n << endl;
                for (int i = 1; i <= n; ++i)
                        cout << p[i].x << " " << p[i].y << " " << p[i].r << endl;
                */
                int ans = 0;
                for (int i = 1; i <= n; ++i) {
                        Point o = p[i];
                        cnt = 0;
                        for (int j = 1; j <= n; ++j) {
                                if (j == i) continue;
                                q[++cnt] = p[j] - o;
                                if (q[cnt].r) reverse(q[cnt]);
                                q[cnt].rad = atan2((double)q[cnt].y,
                                                   (double)q[cnt].x);
                        }
                        sort(q + 1, q + cnt + 1);
                        /*
                        for (int j = 1; j <= cnt; ++j)
                                q[j].print();
                        */
                        int L, R, sum;
                        L = R = 1;
                        sum = 2;
                        for (int j = 1; j < n; ++j) {
                                int next_R = next(R);
                                while (sum < n && cross(q[L], q[next_R]) >= 0) {
                                        R = next_R;
                                        next_R = next(R);
                                        sum++;
                                }
                                ans = max(ans, sum);
                                sum--;
                                L = next(L);
                        }
                }
                cout << ans << endl;
        }
        return 0;
}

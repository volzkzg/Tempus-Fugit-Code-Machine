// O(n^2)
void rebuild(const Point &a, const Point &b) {
        points[n] = points[0];
        int m = 0;
        for (int i = 0; i < n; ++ i) {
                double s_1 = det(b - a, points[i] - a);
                double s_2 = det(b - a, points[i + 1] - a);
                if (signum(s_1) * signum(s_2) < 0) {
                        newPoints[m ++] = (points[i + 1] * s_2 - points[i] * s_1) / (s_2 - s_1);
                }
                if (signum(det(b - a, points[i + 1] - a)) >= 0) {
                        newPoints[m ++] = points[i + 1];
                }
        }
        n = m;
        copy(newPoints, newPoints + n, points);
}

// O(nlogn)
bool check(const Plane &u, const Plane &v, const Plane &w) {
        return intersect(u, v).in(w);
}

void build(vector <Plane> planes) {
        int head = 0;
        int tail = 0;
        for (int i = 0; i < (int)planes.size(); ++ i) {
                while (tail - head > 1 && !check(queue[tail - 2], queue[tail - 1], planes[i])) {
                        tail --;
                }
                while (tail - head > 1 && !check(queue[head + 1], queue[head], planes[i])) {
                        head ++;
                }
                queue[tail ++] = planes[i];
        }
        while (tail - head > 2 && !check(queue[tail - 2], queue[tail - 1], queue[head])) {
                tail --;
        }
        while (tail - head > 2 && !check(queue[head + 1], queue[head], queue[tail - 1])) {
                head ++;
        }
}

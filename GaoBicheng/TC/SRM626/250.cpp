#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 52;

class FixedDiceGameDiv1 {
public:
        vector<double> getProb(int a, int b)
        {
                double f[N][N * N];
                memset(f, 0, sizeof(f));
                f[0][0] = 1.0;
                for (int i = 1; i <= a; ++i) {
                        for (int j = 1; j <= i * b; ++j) {
                                for (int k = 1; k <= b; ++k) {
                                        if (j - k < 0) continue;
                                        f[i][j] += f[i - 1][j - k] / (double)b;
                                }
                        }
                }

                vector<double> ret(a * b + 1, 0.0);
                for (int i = 0; i <= a * b; ++i)
                        ret[i] = f[a][i];
                return ret;
        }

        double getExpectation(int a, int b, int c, int d)
        {
                vector<double> alice = getProb(a, b);
                vector<double> bob = getProb(c, d);

                double pv = 0.0;
                for (int i = 1; i <= a * b; ++i)
                        for (int j = 1; j <= c * d; ++j) 
                                if (i > j) {
                                        pv += alice[i] * bob[j];
                                }

                if (pv <= 0.0) return -1;

                double ev = 0.0;
                for (int i = 1; i <= a * b; ++i)
                        for (int j = 1; j <= c * d; ++j)
                                if (i > j) {
                                        ev += (double)i * alice[i] * bob[j];
                                }
                return ev / pv;
        }
};

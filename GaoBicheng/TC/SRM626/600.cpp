#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 55;
const long long INF = 1e17;

class NegativeGraphDiv1 {
public:
	long long findMin(int n, vector<int> from, vector<int> to, vector<int> weight, int charges) {
		from.push_back(n), to.push_back(n), weight.push_back(0);
		int len = from.size();
		long long dist[N][N], A[N][N];
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) {
				dist[i][j] = INF;
				A[i][j] = INF;
			}
		for (int i = 1; i <= n; ++i)
			dist[i][i] = 0;
		for (int i = 0; i < len; ++i) {
			int u = from[i];
			int v = to[i];
			int w = weight[i];
			dist[u][v] = min((long long)w, dist[u][v]);
		}
		for (int k = 1; k <= n; ++k)
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					if (dist[i][k] + dist[k][j] < dist[i][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
					}

		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				A[i][j] = dist[i][j];
		for (int k = 0; k < len; ++k) {
			int u = from[k];
			int v = to[k];
			int w = weight[k];
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j) {
					A[i][j] = min(A[i][j], dist[i][u] - w + dist[v][j]);
				}
		}
		/*
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j)
				cout << A[i][j] << " " ;
			cout << endl;
		}
		*/
		long long ans[N][N], C[N][N];
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				ans[i][j] = dist[i][j];
		while (charges) {
			if (charges & 1) {
				for (int i = 1; i <= n; ++i)
					for (int j = 1; j <= n; ++j)
						C[i][j] = INF;
				for (int i = 1; i <= n; ++i)
					for (int j = 1; j <= n; ++j)
						for (int k = 1; k <= n; ++k) {
							//if (i == 1 && j == 3) cout << ans[i][k] << " " << A[k][j] << endl;
							C[i][j] = min(ans[i][k] + A[k][j], C[i][j]);
						}
				for (int i = 1; i <= n; ++i)
					for (int j = 1; j <= n; ++j)
						ans[i][j] = C[i][j];
			}
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					C[i][j] = INF;
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					for (int k = 1; k <= n; ++k)
						C[i][j] = min(C[i][j], A[i][k] + A[k][j]);
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					A[i][j] = C[i][j];
			charges >>= 1;
		}
		return ans[1][n];
	}
};

int main()
{
	ios::sync_with_stdio(false);
	NegativeGraphDiv1 test;
	
	int aa[] = {1,1,2,2,3,3};
	int bb[] = {2,3,1,3,1,2};
	int cc[] = {1,5,1,10,1,1};
	
	vector<int> a(aa, aa + sizeof(aa) / sizeof(int));
	vector<int> b(bb, bb + sizeof(bb) / sizeof(int));
	vector<int> c(cc, cc + sizeof(cc) / sizeof(int));
	
	cout << test.findMin(3, a, b, c, 1) << endl;
	return 0;
}

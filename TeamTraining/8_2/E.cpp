#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 500 + 10;
const int MAXM = 50000 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Edge {
        int next, to, w, cost;
} g[MAXM];
int gn, start[MAXN];

inline void AddEdge(int a, int b, int c, int d) {
        gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c; g[gn].cost = d;
        gn++; g[gn].next = start[b]; start[b] = gn; g[gn].to = a; g[gn].w = 0; g[gn].cost = -d;
}

int n, m, N, A[MAXN], B[MAXN], S, T, ans, maxflow;
int q[MAXN], head, tail, dist[MAXN], path[MAXN];
bool vis[MAXN];

bool SPFA() {
        for (int i = 1; i <= N; ++i)
                vis[i] = 0;
        for (int i = 1; i <= N; ++i)
                dist[i] = INF;
        q[head = 0] = S; tail = 1; vis[S] = 1; dist[S] = 0;
        while (head != tail) {
                int p = q[head++];
                if (head == MAXN) head = 0;
                vis[p] = 0;
                for (int i = start[p]; i; i = g[i].next) {
                        if (g[i].w <= 0)
                                continue;
                        int v = g[i].to;
                        if (dist[v] > dist[p] + g[i].cost) {
                                dist[v] = dist[p] + g[i].cost;
                                path[v] = i;
                                if (!vis[v]) {
                                        vis[v] = 1;
                                        if (dist[q[head]] < dist[v]) {
                                                q[tail++] = v;
                                                if (tail == MAXN) tail = 0;
                                        }
                                        else {
                                                --head;
                                                if (head == -1)
                                                        head += MAXN;
                                                q[head] = v;
                                        }
                                }
                        }
                }
        }
        return dist[T] < INF;
}

void Aug() {
        int now = T, delta = INF;
        while (now != S) {
                int i = path[now];
                delta = min(delta, g[i].w);
                now = g[i ^ 1].to;
        }
        ans += dist[T] * delta;
        maxflow += delta;
        now = T;
        while (now != S) {
                int i = path[now];
                g[i].w -= delta;
                g[i ^ 1].w += delta;
                now = g[i ^ 1].to;
        }
}

int main() {
        while (scanf("%d%d", &n, &m) == 2) {
                S = 2 * n + 1; T = S + 1;
                N = T;
                gn = 1; ans = maxflow = 0;
                for (int i = 1; i <= N; ++i)
                        start[i] = 0;
                int suma = 0, sumb = 0;
                for (int i = 1; i <= n; ++i) {
                        int a, b;
                        scanf("%d%d", &a, &b);
                        suma += a;
                        sumb += b;
                        AddEdge(S, i, a, 0);
                        AddEdge(i + n, T, b, 0);
                        AddEdge(i, i + n, INF, 0);
                }
                for (int a, b, i = 1; i <= m; ++i) {
                        scanf("%d%d", &a, &b);
                        AddEdge(a, b + n, INF, 1);
                        AddEdge(b, a + n, INF, 1);
                }
                if (suma != sumb) {
                        puts("-1");
                        continue;
                }
                while (SPFA())
                        Aug();
                if (maxflow != suma) {
                        puts("-1");
                        continue;
                }
                printf("%d\n", ans);
        }

        return 0;
}

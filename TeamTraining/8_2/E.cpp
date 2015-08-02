#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <utility>
using namespace std;

const int Maxn = 500, Maxm = 100000;

class Graph
{
public:
        int head[Maxn], Next[Maxm], No[Maxm], tot;
        int w[Maxm], cost[Maxm];
        void init()
        {
                tot = 2;
                memset(head, 0, sizeof head);
        }
        void add(int x, int y, int flow, int c)
        {
                Next[tot] = head[x];
                head[x] = tot;
                No[tot] = y;
                w[tot] = flow;
                cost[tot++] = c;
        }
        void addedge(int x, int y, int flow, int c)
        {
                add(x, y, flow, c);
                add(y, x, 0, -c);
        }
}G;
int S, T;
const int inf = 0x3f3f3f3f;

int dst[Maxn];
bool inq[Maxn];
int pre[Maxn], preE[Maxn];

bool bfs()
{
        for(int i = 0; i <= T; ++i)
                inq[i] = false, dst[i] = inf;
        queue<int> q;
        q.push(S);
        dst[S] = 0;
        pre[S] = preE[S] = -1;
        while(!q.empty())
                {
                        int cur = q.front(); q.pop();
                        inq[cur] = false;
                        for(int j = G.head[cur]; j; j = G.Next[j])
                                {
                                        int y = G.No[j];
                                        if(G.w[j] == 0) continue;
                                        if(dst[y] > dst[cur] + G.cost[j])
                                                {
                                                        dst[y] = dst[cur] + G.cost[j];
                                                        pre[y] = cur;
                                                        preE[y] = j;
                                                        if(!inq[y])
                                                                inq[y] = true, q.push(y);
                                                }
                                }
                }
        return dst[T] != inf;
}

pair<int, int> costflow()
{
        pair<int, int> ret = make_pair(0, 0);
        while(bfs())
                {
                        int d = inf;
                        int cur = T;
                        while(cur != S)
                                {
                                        int e = preE[cur];
                                        d = min(G.w[e], d);
                                        cur = pre[cur];
                                }
                        ret.first += d;
                        ret.second += d * dst[T];
                        cur = T;
                        while(cur != S)
                                {
                                        int e = preE[cur];
                                        G.w[e] -= d;
                                        G.w[e ^ 1] += d;
                                        cur = pre[cur];
                                }
                }
        return ret;
}

int main()
{
        int n, m;
        while(scanf("%d%d", &n, &m) == 2)
                {
                        G.init();
                        S = 2 * n + 1, T = S + 1;
                        int sumA = 0, sumB = 0;
                        for(int i = 1; i <= n; ++i)
                                {
                                        int x, y;
                                        scanf("%d%d", &x, &y);
                                        G.addedge(S, i, x, 0);
                                        G.addedge(n + i, T, y, 0);
                                        G.addedge(i, n + i, inf, 0);
                                        G.addedge(n + i, i, inf, 0);
                                        sumA += x, sumB += y;
                                }
                        for(int j = 0; j < m; ++j)
                                {
                                        int x, y;
                                        scanf("%d%d", &x, &y);
                                        G.addedge(x, y + n, inf, 1);
                                        G.addedge(y, x + n, inf, 1);
                                }
                        if(sumA != sumB)
                                {
                                        printf("-1\n");
                                        continue;
                                }
                        pair<int, int> c = costflow();
                        if(c.first != sumA)
                                {
                                        printf("-1\n");
                                        continue;
                                }
                        printf("%d\n", c.second);
                }
        return 0;
}

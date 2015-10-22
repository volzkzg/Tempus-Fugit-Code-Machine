#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int oo = 1073741819;

const int Maxn = 200000;
const int Maxm = 200000;

vector<int> g[Maxn];

//idom[i] is the dominator of i, node id -- 1 based(1 ~ n), n is the source
class DominatorTree
{
public:
    int tail[4][Maxm], n, m;
    int Next[4][Maxm], sora[4][Maxm];
    int ss[4], top, w_time;
    int rel[Maxn], semi[Maxn], b[Maxn], idom[Maxn], best[Maxn], st[Maxn], pre[Maxn];
    void origin()
    {
        for (int e = 0; e <= 3; e++) ss[e] = n;
        for (int i = 1; i <= n; i++) {
            for (int e = 0; e <= 3; e++)
                tail[e][i] = i, Next[e][i] = 0;
            rel[i] = 0, semi[i] = idom[i] = pre[i] = 0, best[i] = i;
            b[i] = i;
        }
        rel[0] = oo;
    }
    void link(int e, int x, int y)
    {
        ++ss[e], Next[e][tail[e][x]] = ss[e], tail[e][x] = ss[e], sora[e][ss[e]] = y, Next[e][ss[e]] = 0;
    }
    void dfs(int x, int y)
    {
        ++w_time, rel[x] = w_time;
        st[++top] = x, pre[x] = y;
        for (int i = x, ne; Next[0][i];) {
            i = Next[0][i], ne = sora[0][i];
            if (!rel[ne]) dfs(ne, x);
        }
    }
    int find(int x)
    {
        int y = b[x];
        if (b[x] != x) b[x] = find(b[x]);
        if (rel[semi[best[y]]]<rel[semi[best[x]]])
            best[x] = best[y];
        return b[x];
    }
    //n -- number of vertex, m -- number of edges, e -- edge set
    void init(int _n, int _m, const vector<pair<int, int> > &e)
    {
        n = _n, m = _m;
        origin();
        for (int i = 0; i < m; i++) {
            link(0, e[i].first, e[i].second);
            link(1, e[i].second, e[i].first);
        }
        w_time = 0, top = 0;
        dfs(n, 0);
    }

    void work()
    {
        for (int i = top; i >= 1; i--) {
            int ne = st[i];
            for (int j = ne, na; Next[1][j];) {
                j = Next[1][j], na = sora[1][j];
                if (!rel[na]) continue;
                int y;
                if (rel[na]>rel[ne]) {
                    find(na);
                    y = semi[best[na]];
                }
                else y = na;
                if (rel[y]<rel[semi[ne]]) semi[ne] = y;
            }
            if (ne != n) link(2, semi[ne], ne);
            for (int j = ne, na; Next[2][j];) {
                j = Next[2][j], na = sora[2][j];
                find(na);
                int y = best[na];
                if (semi[y] == semi[na]) idom[na] = semi[na];
                else idom[na] = y;
            }
            for (int j = ne, na; Next[0][j];) {
                j = Next[0][j], na = sora[0][j];
                if (pre[na] == ne) {
                    na = find(na);
                    b[na] = ne;
                }
            }
        }
        for (int i = 2; i <= top; i++) {
            int ne = st[i];
            if (idom[ne] != semi[ne]) idom[ne] = idom[idom[ne]];
            link(3, idom[ne], ne);
        }
    }
}dom;

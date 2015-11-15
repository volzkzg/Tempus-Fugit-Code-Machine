#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

const int MAXN = 100000 + 10;

int dfn[MAXN], low[MAXN], bccno[MAXN], dfn_clock, bcc_cnt, Top;
vector <int> G[MAXN], bcc[MAXN];
pair <int, int> stk[MAXN];
bool iscut[MAXN];
int n, m;

void dfs(int p, int fa) {
    low[p] = dfn[p] = ++dfn_clock;
    int child = 0;
    for (int i = 0; i < G[p].size(); ++i) {
        int v = G[p][i];
        if (!dfn[v]) {
            stk[++Top] = make_pair(p, v);
            dfs(v, p);
            child++;
            low[p] = min(low[p], low[v]);
            if (low[v] >= dfn[p]) {
                iscut[p] = 1;
                ++bcc_cnt;
                bcc[bcc_cnt].clear();
                for (;;) {
                    pair <int, int> x = stk[Top];
                    --Top;
                    if (bccno[x.first] != bcc_cnt) {
                        bccno[x.first] = bcc_cnt;
                        bcc[bcc_cnt].push_back(x.first);
                    }
                    if (bccno[x.second] != bcc_cnt) {
                        bccno[x.second] = bcc_cnt;
                        bcc[bcc_cnt].push_back(x.second);
                    }
                    if (x.first == p && x.second == v)
                        break;
                }
            }
        }
        else
            if (dfn[v] < dfn[p] && v != fa) {
                stk[++Top] = make_pair(p, v);
                low[p] = min(low[p], dfn[v]);
            }
    }
    if (fa < 0 && child == 1) iscut[p] = 0;
}

void find_bcc(int n) {
    for (int i = 1; i <= n; ++i) dfn[i] = 0;
    for (int i = 1; i <= n; ++i) iscut[i] = 0;
    for (int i = 1; i <= n; ++i) bccno[i] = 0;
    dfn_clock = bcc_cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            dfs(i, -1);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int a, b, i = 1; i <= m; ++i) {
        scanf("%d%d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }
    find_bcc(n);

    return 0;
}

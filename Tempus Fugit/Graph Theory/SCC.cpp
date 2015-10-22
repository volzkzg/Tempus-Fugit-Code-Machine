#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

vector <int> G[MAXN];
int n, m;
int dfn[MAXN], low[MAXN], stk[MAXN], Top, scc_cnt, sccno[MAXN], dfn_clock;

void dfs(int p) {
    dfn[p] = low[p] = ++dfn_clock;
    stk[++Top] = p;
    for (int i = 0; i < (int)G[p].size(); ++i) {
        int v = G[p][i];
        if (!dfn[v]) {
            dfs(v);
            low[p] = min(low[p], low[v]);
        }
        else if (!sccno[v])
            low[p] = min(low[p], dfn[v]);
    }
    if (low[p] == dfn[p]) {
        scc_cnt++;
        for (;;) {
            int x = stk[Top];
            --Top;
            sccno[x] = scc_cnt;
            if (x == p) break;
        }
    }
}

void find_scc(int n) {
    dfn_clock = scc_cnt = 0;
    for (int i = 1; i <= n; ++i) sccno[i] = 0;
    for (int i = 1; i <= n; ++i) dfn[i] = low[i] = 0;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            dfs(i);
}

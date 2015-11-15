#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1

using namespace std;

const int MAX = 111111;
typedef long long LL;
typedef vector<int>::iterator iter;
struct qry_node {
    int u,v,w;
}qrys[MAX];
struct tree_node {
    LL sum;
    LL mark;
}tree[MAX*4];
vector<int> ori[MAX];
int pre[MAX],size[MAX],heavy[MAX], deep[MAX], f[MAX][20];
int num[MAX],block[MAX],pathHead[MAX],ind = 0;

void insert(int u,int v)
{
    ori[u].push_back(v);
    ori[v].push_back(u);
}

void prepare_split(int u,int pre)
{
    int tmp = 0;
    pre[u] = pre;
    for (iter it = ori[u].begin(); it != ori[u].end(); ++it) {
        int v = (*it);
        if (v != pre) {
            prepare_split(v,u);
            if (size[v] > tmp) {

                tmp = size[v];
                heavy[u] = v;
            }
            size[u] += size[v];
        }
    }
    size[u]++;
}
 
void split(int u,int bel) 
{
    block[u] = num[u] = ++ind;
    pathHead[u] = bel;
    if (heavy[u]) split(heavy[u],bel);
    block[u] = max(block[u],block[heavy[u]]);
    for (iter it = ori[u].begin(); it != ori[u].end(); ++ it) {
        int v = (*it);
        if (v != pre[u] && heavy[u] != v)  {
            split(v,v);
            block[u] = max(block[u],block[v]);
        }
    }
}

void push_up(int l,int r,int rt)
{
    if (l != r) tree[rt].sum = tree[rt<<1].sum + tree[(rt<<1)+1].sum;
}
void push_down(int l,int r,int rt)
{
    if (tree[rt].mark != 0 && l != r) {
        int mid = (l + r) >> 1;
        tree[rt << 1].mark += tree[rt].mark;
        tree[rt << 1 | 1].mark += tree[rt].mark;
        tree[rt << 1].sum += (mid - l + 1) * tree[rt].mark;
        tree[rt << 1 | 1].sum += (r - mid) * tree[rt].mark;
        tree[rt].mark = 0;
    }
}

void build(int l,int r,int rt)
{
    tree[rt].sum = tree[rt].mark = 0;
    if (l == r) return;
    int mid = (l+r)>>1;
    build(lson);
    build(rson);
}
void upd(int l,int r,int rt,int a,int b,int c)
{
    push_down(l,r,rt);
    int tmp = tree[rt].sum;
    if (a <= l && b >= r) {
        tree[rt].sum += (r - l + 1) * c;
        tree[rt].mark += c;
        return;
    }
    int mid = (l + r) >> 1;
    if (a <= mid) upd(lson,a,b,c);
    if (b > mid) upd(rson,a,b,c);
    push_up(l,r,rt);
}
LL qry(int l,int r,int rt,int a,int b)
{
    push_down(l,r,rt);
    if (a <= l && b >= r) {
        return tree[rt].sum;
    }
    int mid = (l + r) >> 1;
    LL ret = 0;
    if (a <= mid) ret += qry(lson,a,b);
    if (b > mid) ret += qry(rson,a,b);
    return ret;
}

void lca_prepare(int u) 
{
    for (iter it = ori[u].begin();it != ori[u].end(); ++it) {
        int v = (*it);
        if (v != pre[u]) {
            deep[v] = deep[u]+1;
            f[v][0] = u;
            for (int tmp = u,dep = 0; tmp ; f[v][dep+1] = f[tmp][dep] , tmp = f[tmp][dep], dep++);
            lca_prepare(v);
        }
    }
}

int get_lca(int u,int v)
{
    int lose = abs(deep[u] - deep[v]),pos = 0;
    if (deep[u] < deep[v]) swap(u,v);
    while (lose) {
        if (lose & 1) u = f[u][pos];
        pos ++;
        lose >>= 1;
    }
    pos = 0;
    while (u != v) {
        if (f[u][pos] != f[v][pos] || (f[u][pos] == f[v][pos] && !pos)) {
            u = f[u][pos];
            v = f[v][pos];
            pos++;
        }
        else {
            pos--;
        }
    }
    return u;
}

int n,m;

int main()
{
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    ios::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a,b;
        cin >> a >> b;
        a ++ ,b ++ ;
        insert(a,b);
    }
    memset(pre,0,sizeof(pre));
    memset(size,0,sizeof(size));
    prepare_split(1,1);
    split(1,1);
    lca_prepare(1);
    build(1,n,1);
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        string c;
        cin >> c;
        if (c[0] == 'A') {
            int u,v,w,lca;
            cin >> u >> v >> w;
            u++,v++;
            lca = get_lca(u,v);
            while (pathHead[u] != pathHead[lca]) {
                upd(1,n,1,num[pathHead[u]],num[u],w);
                u = pre[pathHead[u]];
            }upd(1,n,1,num[lca],num[u],w);
            while (pathHead[v] != pathHead[lca]) {
                upd(1,n,1,num[pathHead[v]],num[v],w);
                v = pre[pathHead[v]];
            }upd(1,n,1,num[lca],num[v],w);
            upd(1,n,1,num[lca],num[lca],-w);
        }
        else {
            int u;
            cin >> u;
            u++;
            cout << (LL)qry(1,n,1,num[u],block[u]) << endl;
        }
    }
    return 0;
}

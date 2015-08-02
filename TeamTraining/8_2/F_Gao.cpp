#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;
const int maxNum = 1e7 + 10;

bool isPrime[maxNum];
bool ismi[maxNum];

struct node {
        int num, max_num;
} tree[N << 2];
int n, val[N], q;

void push_up(int rt)
{
        tree[rt].num = tree[rt << 1].num + tree[rt << 1 | 1].num;
        tree[rt].max_num = max(tree[rt << 1].max_num,
                               tree[rt << 1 | 1].max_num);
}

int check(int x)
{
        if (ismi[x] || isPrime[x] || x == 6 || x <= 1)
                return 1;
        else
                return 0;
}

void build(int l, int r, int rt)
{
        if (l == r) {
                tree[rt].max_num = val[l];
                tree[rt].num = check(val[l]);
        } else {
                int mid = (l + r) >> 1;
                build(l, mid, rt << 1);
                build(mid + 1, r, rt << 1 | 1);
                push_up(rt);
        }
}

void init()
{
        memset(isPrime, true, sizeof(isPrime));
        memset(ismi, false, sizeof(ismi));
        isPrime[1] = false;
        for (int i = 1; i < maxNum; ++i) {
                if (isPrime[i]) {
                        for (int j = i + i; j < maxNum; j += i)
                                isPrime[j] = false;
                }
        }
        for (int i = 2; i < maxNum; i *= 2)
                ismi[i] = true;
}

int  qry(int l, int r, int rt, int a, int b)
{
        if (a > r || b < l) return 0;
        if (a <= l && b >= r) {
                return tree[rt].num;
        } else {
                int mid = (l + r) >> 1;
                int ret = 0;
                if (a <= mid) ret += qry(l, mid, rt << 1, a, b);
                if (b > mid) ret += qry(mid + 1, r, rt << 1 | 1, a, b);
                return ret;
        }
}


void upd_mod(int l, int r, int rt, int a, int b, int v)
{
        if (tree[rt].max_num < v) return;
        if (l == r) {
                val[l] %= v;
                tree[rt].max_num = val[l];
                tree[rt].num = check(val[l]);
        } else {
                int mid = (l + r) >> 1;
                if (a <= mid) upd_mod(l, mid, rt << 1, a, b, v);
                if (b > mid) upd_mod(mid + 1, r, rt << 1 | 1, a, b, v);
                push_up(rt);
        }
}

void upd_modify(int l, int r, int rt, int p, int x)
{
        if (l == r) {
                val[l] = x;
                tree[rt].max_num = val[l];
                tree[rt].num = check(val[l]);
        } else {
                int mid = (l + r) >> 1;
                if (p <= mid) upd_modify(l, mid, rt << 1, p, x);
                if (p > mid) upd_modify(mid + 1, r, rt << 1 | 1, p, x);
                push_up(rt);
        }
}

int main()
{
        ios::sync_with_stdio(false);
        init();
        while (cin >> n) {
                for (int i = 1; i <= n; ++i)
                        cin >> val[i];
                build(1, n, 1);
                cin >> q;
                for (int i = 1; i <= q; ++i) {
                        int mode, L, R, v, x, p;
                        cin >> mode;
                        if (mode == 1) {
                                cin >> L >> R;
                                cout << qry(1, n, 1, L, R) << endl;
                        } else if (mode == 2) {
                                cin >> L >> R >> v;
                                upd_mod(1, n, 1, L, R, v);
                        } else {
                                cin >> p >> x;
                                upd_modify(1, n, 1, p, x);
                        }
                }
        }
        return 0;
}

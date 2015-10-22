#include <iostream>
#include <cstdio>
#include <cstdlib>
#define keyTree root->ch[1]->ch[0]

using namespace std;

const int N = 500000;
const int INF = 1001;
int n, m, a[N];

int max(int x, int y, int z)
{
    return max(x, max(y, z));
}

struct node {
    int key, maxL, maxR, maxSum, sum, same, size;
    bool rev;
    node *pre, *ch[2];
    inline void reverse(){
        if (size == 0) return;
        rev ^= 1;
        swap(ch[0], ch[1]);
        swap(maxL, maxR);
    }
    inline void saming(int x){
        if (size == 0) return;
        key = same = x;
        maxL = maxR = maxSum = sum = x * size;
        if (x < 0)
            maxL = maxR = maxSum  = x;
    }
    inline void push_up(){
        sum = ch[0]->sum + ch[1]->sum + key;
        size = ch[0]->size + ch[1]->size + 1;
        maxL = max(ch[0]->maxL, ch[0]->sum+key, ch[0]->sum+key+ch[1]->maxL);
        maxR = max(ch[1]->maxR, ch[1]->sum+key, ch[1]->sum+key+ch[0]->maxR);
        maxSum = max(ch[0]->maxSum,max(ch[1]->maxSum,max(ch[0]->maxR+key,max(ch[1]->maxL+key,max(ch[0]->maxR+key+ch[1]->maxL,key)))));
    }
    inline void push_down(){
        if (rev){
            ch[0]->reverse();
            ch[1]->reverse();
        }
        rev = 0;
        if (same != INF){
            ch[0]->saming(same);
            ch[1]->saming(same);
        }
        same = INF;
    }
};

class splayTree{
public:
    node *root, *null;
    node buf[N]; // 内存池
    int top; // 内存池使用量
    node *stk[N]; // 内存回收
    int cnt; // 内存回收量
    int num;
    int pos, tot, c, pop;
    inline void erase(node *x){
        x->size = x->sum = x->maxL = x->maxR = x->maxSum = 0;
    }
    inline node *newNode(int value){
        node *x;
        if (cnt) x = stk[cnt--];
        else x = &buf[top++];
        x->key = x->maxL = x->maxR = x->maxSum = x->sum = value;
        x->size = 1, x->rev = 0;
        x->pre = x->ch[0] = x->ch[1] = null;
        x->same = INF;
        return x;
    }
    inline void init(){
        top = cnt = 0;
        num = n;
        null = newNode(-INF);
        null->size = 0, null->sum = 0;
        root = newNode(-INF);
        root->sum = 0;
        root->ch[1] = newNode(-INF);
        root->ch[1]->pre = root;
        root->ch[1]->sum =0;
    }
    inline node *build(int l,int r){
        if (l>r) return null;
        int mid = (l+r) >> 1;
        node *x = newNode(a[mid]);
        x->ch[0] = build(l,mid-1);
        x->ch[1] = build(mid+1,r);
        if (x->ch[0] != null) x->ch[0]->pre = x;
        if (x->ch[1] != null) x->ch[1]->pre = x;
        x->push_up();
        return x;
    }
    inline void rotate(node *x,int c){
        node *y = x->pre;
        y->push_down();
        x->push_down();
        y->ch[!c] = x->ch[c];
        if (y->ch[!c] != null)
            y->ch[!c]->pre = y;
        x->pre = y->pre;
        if (x->pre != null)
            x->pre->ch[y == x->pre->ch[1]] = x;
        x->ch[c] = y;
        y->pre = x;
        if (y == root)
            root = x;
        y->push_up();
    }
    inline void splay(node *x, node *g){
        x->push_down();
        while (x->pre != g){
            if (x->pre->pre == g){
                rotate(x, x == x->pre->ch[0]);
                break;
            }
            node *y = x->pre, *z = y->pre;
            int f = (y == z->ch[0]);
            if (x == y->ch[f])
                rotate(x, !f), rotate(x, f);
            else
                rotate(y, f), rotate(x, f);
        }
        x->push_up();
    }
    inline void select(node *x, int k){
        node *t = root;
        while (true) {
            t->push_down();
            int tmp = t->ch[0]->size;
            if (tmp == k) break;
            if (tmp < k) k -= tmp + 1, t = t->ch[1];
            else t = t->ch[0];
        }
        splay(t, x);
    }
    inline void recycle(node *x){
        if (x->ch[0] != null) recycle(x->ch[0]);
        stk[++cnt] = x;
        if (x->ch[1] != null) recycle(x->ch[1]);
    }
    inline void insert(){
        scanf("%d%d", &pos, &tot);
        num += tot;
        for (int i = 1; i <= tot; ++i)
            scanf("%d", &a[i]);
        select(null, pos);
        select(root, pos+1);
        keyTree = build(1, tot);
        keyTree->pre = root->ch[1];
        splay(keyTree, null);
    }
    inline void del(){
        scanf("%d%d", &pos, &tot);
        select(null, pos-1);
        select(root, pos+tot);
        if (keyTree != null){
            num -= keyTree->size;
            recycle(keyTree);
            root->ch[1]->ch[0] = null;
            root->ch[1]->push_up();
            root->push_up();
        }
        splay(root->ch[1], null);
    }
    inline void make_same(){
        scanf("%d%d%d", &pos, &tot, &c);
        select(null, pos-1);
        select(root, pos+tot);
        if (keyTree != null){
            keyTree->saming(c);
            splay(keyTree, null);
        }
    }
    inline void reverse(){
        scanf("%d%d", &pos, &tot);
        select(null, pos-1);
        select(root, pos+tot);
        if (keyTree != null){
            keyTree->reverse();
            splay(keyTree, null);
        }
    }
    inline void max_sum(){
        printf("%d\n", root->maxSum);
    }
    inline void get_sum(){
        scanf("%d%d", &pos, &tot);
        select(null, pos-1);
        select(root, pos+tot);
        if (keyTree != null){
            printf("%d\n", keyTree->sum);
            splay(keyTree, null);
            keyTree->push_down();
        } else printf("0\n");
    }
}spt;

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    spt.init();
    spt.keyTree = spt.build(1,n);
    spt.keyTree->pre = spt.root->ch[1];
    spt.splay(spt.keyTree, spt.null);
    char op[30];
    for (int i = 1; i <= m; ++i) {
        scanf("%s", op);
        switch (op[0]){
        case 'I': spt.insert(); break;
        case 'D': spt.del(); break;
        case 'R': spt.reverse(); break;
        case 'G': spt.get_sum(); break;
        case 'S': spt.make_same(); break;
        case 'M':
            if (op[2] == 'X') spt.max_sum();
            else spt.make_same(); break;
        }
    }
    return 0;
}

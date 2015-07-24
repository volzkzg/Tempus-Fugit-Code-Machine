#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 200020
#define M 8005000
struct xy{int o,num;}a[N];
int cmp(xy a,xy b){return a.num < b.num;}
int root[N],n,q;
int ls[M],rs[M],lm[M],rm[M],sum[M];
int cnt;
void push_up(int k){
   sum[k] = sum[ls[k]] + sum[rs[k]];
   lm[k] = max(lm[ls[k]],sum[ls[k]] + lm[rs[k]]);
   rm[k] = max(rm[rs[k]],sum[rs[k]] + rm[ls[k]]);
}
void build(int &rt,int l,int r){
   rt = ++ cnt;
   if (l == r) {
       lm[rt] = rm[rt] = sum[rt] = 1;
       return;
   }
   int m = l + r >> 1;
   build(ls[rt],l,m);
   build(rs[rt],m + 1,r);
   push_up(rt);
}
void update(int last,int l,int r,int &rt,int k,int val){
   rt = ++ cnt;
   ls[rt] = ls[last],rs[rt] = rs[last];
   if (l == r){
       sum[rt] = lm[rt] = rm[rt] = val;
       return;
   }
   int m = l + r >> 1;
   if (k <= m) update(ls[last],l,m,ls[rt],k,val);
   else update(rs[last],m + 1,r,rs[rt],k,val);
   push_up(rt);
}
int qall(int rt,int l,int r,int x,int y){
   if (l == x && r == y) return sum[rt];
   int m = l + r >> 1;
   if (y <= m) return qall(ls[rt],l,m,x,y);
   else if (x > m) return qall(rs[rt],m + 1,r,x,y);
   else return qall(ls[rt],l,m,x,m) + qall(rs[rt],m + 1,r,m + 1,y);
}
int ql(int rt,int l,int r,int x,int y){
   if (l == x && r == y) return lm[rt];
   int m = l + r >> 1;
   if (y <= m) return ql(ls[rt],l,m,x,y);
   else if (x > m) return ql(rs[rt],m + 1,r,x,y);
   else return max(ql(ls[rt],l,m,x,m),qall(ls[rt],l,m,x,m) + ql(rs[rt],m + 1,r,m + 1,y));
}
int qr(int rt,int l,int r,int x,int y){
   if (l == x && r == y) return rm[rt];
   int m = l + r >> 1;
   if (y <= m) return qr(ls[rt],l,m,x,y);
   else if (x > m) return qr(rs[rt],m + 1,r,x,y);
   else return max(qr(rs[rt],m + 1,r,m + 1,y),qall(rs[rt],m + 1,r,m + 1,y) + qr(ls[rt],l,m,x,m));
}
int check(int k,int a,int b,int c,int d){
   int ret = 0;
   if (c > b + 1) ret = qall(root[k],0,n - 1,b + 1,c - 1);
   ret += ql(root[k],0,n - 1,c,d);
   ret += qr(root[k],0,n - 1,a,b);
   return ret >= 0;
}
int main(){
   scanf("%d",&n);
   for (int i = 0;i < n;i ++){
       a[i].o = i;
       scanf("%d",&a[i].num);
   }
   sort(a,a + n,cmp);
   build(root[0],0,n - 1);
   for (int i = 1;i < n;i ++) update(root[i - 1],0,n - 1,root[i],a[i - 1].o,-1);
   scanf("%d",&q);
   int ans = 0,p[4];
   while (q --){
       scanf("%d%d%d%d",&p[0],&p[1],&p[2],&p[3]);
       for (int i = 0;i < 4;i ++) p[i] = (ans + p[i]) % n;
       sort(p,p + 4);
       int l = 0,r = n,mid;
       while (l < r - 1){
           mid = l + r >> 1;
           if (check(mid,p[0],p[1],p[2],p[3])) l = mid;
           else r = mid;
       }
       ans = a[l].num;
       printf("%d\n",ans);
   }
   return 0;
}
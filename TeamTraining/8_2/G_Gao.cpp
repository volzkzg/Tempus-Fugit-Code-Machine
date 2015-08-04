#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

#define Mod mod
#define ll long long
using namespace std;

const int maxn = 100000+10;
int n,m,a[maxn],b[maxn];
const int mod = 998244353;

int gcd(int a,int b) { return b==0?a:gcd(b,a%b); }

struct no{
        int lmax,lmin,x;
        bool operator<(const no &rhs)const{
                if(x!=rhs.x) return x<rhs.x;
                return lmax>rhs.lmax;
        }
}q1[maxn*30],q2[maxn*30];
int tot1,tot2,nxt[maxn];
ll ans1,ans2;

void fenjie(int a[],int n,no q[],int &tot){
        tot=0; int val[maxn];
        q[tot++]=(no) { 1,1,a[1] };
        nxt[1]=1,val[1]=a[1];
        for(int i=2;i<=n;i++){
                nxt[i]=i,val[i]=a[i];
                int pos=i;
                while(pos>0){
                        val[pos]=gcd(val[pos],a[i]);
                        while(nxt[pos]>1&&gcd(val[nxt[pos]-1],val[pos])==val[pos]){
                                nxt[pos]=nxt[nxt[pos]-1];
                        }
                        q[tot++]=(no){ i-nxt[pos]+1,i-pos+1,val[pos] };
                        pos=nxt[pos]-1;
                }
        }
        sort(q,q+tot);
}

void solve(){
        ans1=ans2=0;
        for(int i=0,j=0;i<tot1&&j<tot2;){
                bool flag=false;
                ll tmp=0,num1=0,num2=0;
                if(q1[i].x<q2[j].x) i++;
                else if(q1[i].x>q2[j].x) j++;
                else{
                        if(q1[i].lmax<q2[j].lmin) j++;
                        else if(q1[i].lmin>q2[j].lmax) i++;
                        else{
                                if(q1[i].lmax>=q2[j].lmin&&q1[i].lmax<=q2[j].lmax){
                                        tmp=q1[i].lmax,flag=true,num1=1,num2=1;
                                        while(i+1<tot1&&q1[i+1].x==q1[i].x&&q1[i+1].lmax>=q1[i].lmax) { num1++; i++; }
                                        while(j+1<tot2&&q2[j+1].x==q2[j].x&&q2[j+1].lmax>=q1[i].lmax){
                                                if(q2[j+1].lmin<=q1[i].lmax) num2++;
                                                j++;
                                        }
                                }
                                else if(q2[j].lmax>=q1[i].lmin&&q2[j].lmax<=q1[i].lmax){
                                        tmp=q2[j].lmax,flag=true,num1=1,num2=1;
                                        while(j+1<tot2&&q2[j+1].x==q2[j].x&&q2[j+1].lmax>=q2[j].lmax) { num2++; j++; }
                                        while(i+1<tot1&&q1[i+1].x==q1[i].x&&q1[i+1].lmax>=q2[j].lmax){
                                                if(q1[i+1].lmin<=q2[j].lmax) num1++;
                                                i++;
                                        }
                                }
                        }
                }
                if(flag){
                        if(tmp>ans1) { ans1=tmp,ans2=num1*num2; }
                        else if(tmp==ans1) { ans2=ans2+num1*num2; }
                        while(i+1<tot1&&q1[i+1].x==q1[i].x) i++;
                        while(j+1<tot2&&q2[j+1].x==q2[j].x) j++;
                        i++,j++;
                }
        }
        printf("%lld %lld\n",ans1,ans2);
}

int main(){
        while(scanf("%d%d",&n,&m)!=EOF){
                for(int i=1;i<=n;i++) scanf("%d",&a[i]);
                for(int j=1;j<=m;j++) scanf("%d",&b[j]);
                fenjie(a,n,q1,tot1);
                fenjie(b,m,q2,tot2);
                solve();
        }
        return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

void solve() {
}

struct edge{
	int t,u,v;
	edge *op,*nxt;
	void init(const int _s,const int _t,const int _u,const int _v,edge *_op);
}e[2001],*V[301],*pe;

void edge::init(const int _s,const int _t,const int _u,const int _v,edge *_op){
	t=_t,u=_u,v=_v,nxt=V[_s],V[_s]=this,op=_op;
}

int n,m;

int a[100],b[100],c[100];
int A,B;

vector<int> FV;
bool vis[300];
bool inpath[300];
int ans;
bool dfs(int x){
	if(x==B+B-1){
		return true;
	}
	vis[x]=1;
	for(edge *ii=V[x];ii;ii=ii->nxt){
		if(!vis[ii->t]&&ii->u){
			if(dfs(ii->t)){
				--ii->u;
				ans+=ii->v;
				++ii->op->u;
				return 1;
			}
		}
	}
	return 0;
}

int dis[301];
int pre[301];
edge *pree[301];
int T;
bool findPath(){
	for(int i=0;i<=T;++i){
		pre[i]=-1,dis[i]=0;
	}
	for(int i=1;i<=T;++i){
		for(int j=0;j<=T;++j){
			for(edge *ii=V[j];ii;ii=ii->nxt) if(ii->u&&ii->v+dis[j]>dis[ii->t]){
				dis[ii->t]=dis[j]+ii->v;
				pre[ii->t]=j;
				pree[ii->t]=ii;
			}
		}
	}
/*	printf("!!!!\n");
	for(int i=0;i<=T;++i) printf("%d ",dis[i]);
	printf("\n!!!!\n");*/
	bool flag=false;
	for(int j=0;j<=T;++j){
		for(edge *ii=V[j];ii;ii=ii->nxt) if(ii->u&&ii->v+dis[j]>dis[ii->t]){
			dis[ii->t]=dis[j]+ii->v;
			pre[ii->t]=j;
			pree[ii->t]=ii;
			flag=true;
		}
	}
	return flag;
}

void elim(){
	memset(vis,0,sizeof(vis));
	vector<int> rec;
	for(int i=0;i<=T;++i){
		if(!vis[i]){
			rec.clear();
			int j=i;
			while(!vis[j]){
				vis[j]=inpath[j]=1;
				rec.push_back(j);
				j=pre[j];
			}
			if(inpath[j]){
				int k=0;
				while(rec[k]!=j) ++k;
				int minval=10000;
				for(int l=k;l<(int)rec.size();++l){
					minval=min(minval,pree[rec[l]]->u);
				}
				for(int l=k;l<(int)rec.size();++l){
					edge *ii=pree[rec[l]];
					ii->u-=minval;
					ii->op->u+=minval;
					ans+=minval*ii->v;
				}
			}
			for(int k=0;k<(int)rec.size();++k){
				inpath[rec[k]]=0;
			}
		}
	}
}

int main() {
	pe=e;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n+m;++i){
		scanf("%d%d%d",a+i,b+i,c+i);
		FV.push_back(b[i]);
		FV.push_back(c[i]);
	}
	sort(FV.begin(),FV.end());
	FV.resize(unique(FV.begin(),FV.end())-FV.begin());
	for(int i=1;i<=n+m;++i){
		c[i]=lower_bound(FV.begin(),FV.end(),c[i])-FV.begin();
		b[i]=lower_bound(FV.begin(),FV.end(),b[i])-FV.begin();
	}
	A=0,B=(int)FV.size();
	T=B+B-1;
	for(int i=0;i<B-1;++i){
		pe->init(i,i+1,10000,0,pe+1);
		++pe;
		pe->init(i+1,i,0,0,pe-1);
		++pe;
		pe->init(B+i,B+i+1,10000,0,pe+1);
		++pe;
		pe->init(B+i+1,B+i,0,0,pe-1);
		++pe;
	}
	for(int i=1;i<=n+m;++i){
		int x=b[i],y=c[i];
		if(i<=n) y+=B;
		else x+=B;
		int v=(i<=n);
		pe->init(x,y,a[i],v,pe+1);
		++pe;
		pe->init(y,x,0,-v,pe-1);
		++pe;
	}
	if(!dfs(0)) printf("0\n");
	else{
		while(findPath()){
			elim();
		}
		printf("%d\n",ans);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

const int Maxn = 2000000, Maxm = 2000000;

class Graph
{
public:
	int head[Maxn], Next[Maxm], No[Maxm], flow[Maxm], tot;
	void init(int n)
	{
		tot = 2;
		for(int i = 0; i <= n + 10; ++i)
			head[i] = 0;
	}
	void add(int x, int y, int f)
	{
		Next[tot] = head[x];
		head[x] = tot;
		No[tot] = y;
		flow[tot++] = f;
	}
	void addedge(int x, int y, int f)
	{
		add(x, y, f);
		add(y, x, 0);
	}
}G;

const int MaxSize = 1050;

int w[MaxSize][MaxSize], n, m, p, q, S, T, ans;
pair<int, int> green[Maxn], red[Maxn];
int mark[MaxSize][MaxSize];
const int RED = 1, WHITE = 0, GREEN = 2;
const int dx[] = {1,1,-1,-1,3,3,-3,-3};
const int dy[] = {3,-3,3,-3,1,-1,1,-1};
const int inf = 0x3f3f3f3f;

class edge
{
public:
	int x, y, f, edgeID;
	edge(){}
	edge(int x, int y, int f):x(x), y(y), f(f){}
};
edge e[Maxm];
int etot;
int relatedEdge[Maxn][2];

void init(int iCase)
{
	ans = 0;
	scanf("%d%d", &n, &m);
	S = 2 * n * m; T = S + 1;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
		{
			scanf("%d", &w[i][j]);
		}
	scanf("%d", &p);
	memset(mark, 0, sizeof mark);
	for(int i = 0; i < p; ++i)
	{
		scanf("%d%d", &green[i].first, &green[i].second);
		mark[green[i].first][green[i].second] = GREEN;
		ans += w[green[i].first][green[i].second];
		for(int k = 0; k < 8; ++k)
		{
			int nx = green[i].first + dx[k], ny = green[i].second + dy[k];
			if(nx < 0 || nx >= n || ny < 0 || ny >= m)
				continue;
			mark[nx][ny] = RED;
		}
	}
	scanf("%d", &q);
	
	for(int i = 0; i < q; ++i)
	{
		scanf("%d%d", &red[i].first, &red[i].second);
		mark[red[i].first][red[i].second] = RED;
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			if(mark[i][j] == WHITE && w[i][j] > 0)
				ans += w[i][j];
}


void BuildEdgeList()
{
	etot = 0;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
		{
			int id = i * m + j;
			if(mark[i][j] != WHITE) continue;
			e[etot++] = edge(id * 2, id * 2 + 1, inf);
			relatedEdge[id][0] = etot;
			relatedEdge[id][1] = etot + 1;
			if(i % 2)
			{
				if(w[i][j] > 0)
				{
					e[etot++] = edge(S, id * 2, w[i][j]);
					e[etot++] = edge(id * 2 + 1, T, 0);
				}
				else
				{
					e[etot++] = edge(S, id * 2, 0);
					e[etot++] = edge(id * 2 + 1, T, -w[i][j]);
				}
				for(int k = 0; k < 8; ++k)
				{
					int nx = i + dx[k], ny = j + dy[k];
					if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
					int idA = id, idB = nx * m + ny;
					if(mark[nx][ny] != WHITE)
						continue;
					e[etot++] = edge(idA * 2, idB * 2 + 1, inf);
				//	e[etot++] = edge(idB * 2, idA * 2 + 1, inf);
				}
			}
			else
			{
				if(w[i][j] > 0)
				{
					e[etot++] = edge(id * 2 + 1, T, w[i][j]);
					e[etot++] = edge(S, id * 2, 0);
				}
				else
				{
					e[etot++] = edge(id * 2 + 1, T, 0);
					e[etot++] = edge(S, id * 2, -w[i][j]);
				}
			}
		}
}

void BuildGraph()
{
	G.init(2 * n * m);
	for(int i = 0; i < etot; ++i)
	{
		e[i].edgeID = G.tot;
		G.addedge(e[i].x, e[i].y, e[i].f);
	}
}

bool AccessFROMS[Maxn], AccessFROMT[Maxn];
int current[Maxn], dst[Maxn];
bool bfs()
{
	static int q[Maxn];
	int l, r; l = r = -1;
	for(int i = 0; i <= T; ++i)
		current[i] = G.head[i], dst[i] = -1;
	dst[S] = 0;
	q[++r] = S;
	while(l < r)
	{
		int cur = q[++l];
		for(int i = G.head[cur]; i; i = G.Next[i])
		{
			int y = G.No[i];
			if(G.flow[i] == 0) continue;
			if(dst[y] == -1)
			{
				dst[y] = dst[cur] + 1;
				q[++r] = y;
			}
		}
	}
	return dst[T] != -1;
}

void bfs2()
{
	static int q[Maxn];
	int l, r; l = r = -1;
	static bool vis[Maxn];
	for(int i = 0; i <= T; ++i)
		vis[i] = false;
	vis[S] = true;
	q[++r] = S;
	while(l < r)
	{
		int cur = q[++l];
		AccessFROMS[cur] = true;
		for(int i = G.head[cur]; i; i = G.Next[i])
		{
			int y = G.No[i];
			if(G.flow[i] == 0) continue;
			if(!vis[y])
			{
				vis[y] = true;
				q[++r] = y;
			}
		}
	}
}

void bfs3()
{
	static int q[Maxn];
	int l, r; l = r = -1;
	static bool vis[Maxn];
	for(int i = 0; i <= T; ++i)
		vis[i] = false;
	vis[T] = true;
	q[++r] = T;
	while(l < r)
	{
		int cur = q[++l];
		AccessFROMT[cur] = true;
		for(int i = G.head[cur]; i; i = G.Next[i])
		{
			int y = G.No[i];
			if(G.flow[i ^ 1] == 0) continue;
			if(!vis[y])
			{
				vis[y] = true;
				q[++r] = y;
			}
		}
	}
}

int dfs(int cur, int flow)
{
	if(cur == T || flow == 0) return flow;
	int orig = flow;
	for(int &i = current[cur]; i; i = G.Next[i])
	{
		int y = G.No[i];
		if(dst[y] != dst[cur] + 1) continue;
		int tmp = dfs(y, min(flow, G.flow[i]));
		flow -= tmp;
		G.flow[i] -= tmp;
		G.flow[i ^ 1] += tmp;
		if(flow == 0)
			return orig;
	}
	dst[cur] = -1;
	return orig - flow;
}


int maxFlow()
{
	int ret = 0;
	BuildGraph();
	while(bfs())
	{
		ret += dfs(S, inf);
	//	printf("%d\n", ret);
	}
	return ret;
}

bool specialBFS(int S)
{
	static bool vis[Maxn];
	static int q[Maxn];
	for(int i = 0; i <= T; ++i)
		vis[i] = false;
	int l, r;
	l = r = -1;
	q[++r] = S;
	vis[S] = true;
	while(l < r)
	{
		int cur = q[++l];
		for(int i = G.head[cur]; i; i = G.Next[i])
		{
			int y = G.No[i];
			if(vis[y] || G.flow[i] == 0) continue;
			vis[y] = true;
			q[++r] = y;
		}
		if(vis[T]) return true;
	}
	return false;
}

void GETLEXMIN_AND_PRINT_ANSWER(int MxFlow)
{
	memset(AccessFROMT, false, sizeof AccessFROMT);
	memset(AccessFROMS, false, sizeof AccessFROMS);
	bfs3(), bfs2();
	static bool solu[31][31];
	memset(solu, false, sizeof solu);
	int sel = 0;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			if(mark[i][j] == GREEN)
				sel += w[i][j];
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			if(mark[i][j] != WHITE) continue;
			int id = i * m + j;
			edge sav1 = e[relatedEdge[id][0]];//, sav2 = e[relatedEdge[id][1]];
		//	e[relatedEdge[id][0]].f = inf;
			int store = G.flow[sav1.edgeID];
			if(G.flow[sav1.edgeID] != 0)
			{
				solu[i][j] = true;
				sel += w[i][j];
				continue;
			}
			G.flow[sav1.edgeID] = inf;
		//	cout << "GTOT "<< G.tot << endl;
			int st = sav1.x;
			if(sav1.x == T || sav1.y == T)
			{
				if(sav1.x == T)
					st = sav1.y;
				else
					st = sav1.x;
				if(!AccessFROMS[st] || (w[i][j] == 0 && !specialBFS(S)))
				{
					AccessFROMT[st] = true;
					static int q[Maxn];
					int l, r;
					l = r = -1;
					q[++r] = st;
					while(l < r)
					{
						int cur = q[++l];
						AccessFROMT[cur] = true;
						for(int i = G.head[cur]; i; i = G.Next[i])
						{
							int y = G.No[i];
							if(!AccessFROMT[y] && G.flow[i ^ 1] && y != T)
							{
								q[++r] = y;
								AccessFROMT[y] = true;
							}
						}
					}
					solu[i][j] = true, sel += w[i][j];
				}
				else
					G.flow[sav1.edgeID] = store;
			}
			else
			{
				if(sav1.x == S)
					st = sav1.y;
				else
					st = sav1.x;
				if(!AccessFROMT[st] || (w[i][j] == 0 && !specialBFS(S)))
				{
					AccessFROMS[st] = true;
					static int q[Maxn];
					int l, r;
					l = r = -1;
					q[++r] = st;
					while(l < r)
					{
						int cur = q[++l];
						AccessFROMS[cur] = true;
						for(int i = G.head[cur]; i; i = G.Next[i])
						{
							int y = G.No[i];
							if(!AccessFROMS[y] && G.flow[i] && y != S)
							{
								q[++r] = y;
								AccessFROMS[y] = true;
							}
						}
					}
					solu[i][j] = true, sel += w[i][j];
				}
				else
					G.flow[sav1.edgeID] = store;
			}
		}
	}
	vector<pair<int, int> > answer;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
		{
			if(solu[i][j] || mark[i][j] == GREEN)
				answer.push_back(make_pair(i, j));
		}
	if(answer.size() == 0)
	{
		//means no GREEN no positive non-RED
		int mx = -0x3f3f3f3f;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
			{
				if(w[i][j] > mx && mark[i][j] != RED)
				{
					mx = w[i][j];
				}
			}
		printf("%d\n", mx);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
			{
				if(w[i][j] == mx && mark[i][j] != RED)
				{
					printf("%d %d\n", i, j);
					return;
				}
			}
		return;
	}
	printf("%d\n", ans - MxFlow);
	bool hasAns = false;
	for(int i = 0; i < answer.size(); ++i)
	{
		bool flag = true;
		for(int j = i; j < answer.size(); ++j)
		{
			if(mark[answer[j].first][answer[j].second] == GREEN || w[answer[j].first][answer[j].second])
			{
				flag = false;
				break;
			}
		}
		if(flag) break;
		hasAns = true;
		printf("%d %d\n", answer[i].first, answer[i].second);
	}
	if(!hasAns)
	{
		printf("%d %d\n", answer[0].first, answer[0].second);
	}
}

int Test;
void solve()
{
	BuildEdgeList();
	int MxFlow = maxFlow();
	GETLEXMIN_AND_PRINT_ANSWER(MxFlow);
}

int main()
{
	scanf("%d", &Test);
	for(int iCase = 1; iCase <= Test; ++iCase)
	{
		printf("Case %d: ", iCase);
		init(iCase);
		solve();
	}
	return 0;
}
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;
const int Maxn = 50000 + 100;
const int Maxm = 11;
const int Maxk = 33;
class SAM
{
public:
	int in[Maxn * 2][Maxm], fa[Maxn * 2], max[Maxn * 2], tot, last;
	int min[Maxn * 2], R[Maxn * 2];
	int cnt[Maxn * 2];
	vector<int> nxt[Maxn * 2];
	SAM()
	{
		tot = last = 0;
		memset(in, -1, sizeof in), memset(fa, -1, sizeof fa);
	}
	void init(int n)
	{
		for(int i = 0; i <= 2 * n + 10; ++i)
		{
			memset(in[i], -1, sizeof in[i]);
			fa[i] = -1;
			R[i] = -1;
			nxt[i].clear();
			cnt[i] = 0;
		}
		tot = last = 0;
	}
	void add(int x, int id)
	{
		int v = last;
		++tot, last = tot, max[last] = max[v] + 1;
		R[last] = id;
		while(v != -1 && in[v][x] == -1) in[v][x] = last, v = fa[v];
		if(v == -1)
		{
			fa[last] = 0;
			return;
		}
		int p = in[v][x];
		if(max[p] == max[v] + 1) fa[last] = p;
		else
		{
			int np = ++tot;
			max[np] = max[v] + 1;
			fa[np] = fa[p], fa[p] = np, fa[last] = np;
			while(v != -1 && in[v][x] == p) in[v][x] = np, v = fa[v];
			memcpy(in[np], in[p], sizeof in[p]);
			//in[np][0] = in[p][0], in[np][1] = in[p][1];
		}
	}
}sam;

char s[Maxn]; int k;
int len;
int ans[Maxk];
int pow10[Maxn];
int f[Maxk][Maxn];
int suffixSum[Maxn];

void dfsSolve(int x, int remain, int l)
{
	int R = sam.R[x];
	for(; l < sam.max[x] && sam.cnt[x] != 1; ++l)
	{
		remain = (remain + pow10[l] * (s[R - l] - '0')) % k;
	//	cout << R - l << " " << R << endl;
		if(s[R - l] != '0')
			ans[remain] -= sam.cnt[x] - 1;
	}
	if(sam.cnt[x] == 1)
	{
		int curSum = (suffixSum[R - sam.max[x] + 1] - suffixSum[R + 1]);
		curSum = (curSum % k + k) % k;
		remain = (remain + f[curSum][len - R] * pow10[l]) % k;
	}
	for(int i = 0; i < sam.nxt[x].size(); ++i)
		dfsSolve(sam.nxt[x][i], remain, sam.max[x]);
}

void init(char *s, int len)
{
	memset(ans, 0, sizeof ans);
	suffixSum[len] = suffixSum[len + 1] = 0;
	for(int i = len - 1; i >= 0; --i)
		suffixSum[i] = (suffixSum[i + 1] + (s[i] - '0') * pow10[(len - 1) - i]) % k;
	for(int i = 0; i < k; ++i)
	{
		for(int j = 0; j <= len; ++j)
		{
			int res = i * pow10[j] % k;
			f[res][j] = i;
		}
	}
	static int delta[Maxk], sum[Maxk];
	memset(sum, 0, sizeof sum);
	bool zero = false;
	for(int i = 0; i < len; ++i)
	{
		memset(delta, 0, sizeof delta);
		int cur = s[i] - '0';
		for(int j = 0; j < k; ++j)
		{
			delta[(j * 10 + cur) % k] += sum[j];
		}
		if(cur != 0)
			delta[cur % k]++;
		else zero = true;
		for(int j = 0; j < k; ++j)
			ans[j] += delta[j], sum[j] = delta[j];
	}
	ans[0] += zero;
}

int main()
{
	while(scanf("%s%d", s, &k) == 2)
	{
		pow10[0] = 1;
		len = strlen(s);
		for(int i = 1; i <= len; ++i)
			pow10[i] = pow10[i - 1] * 10 % k;
		sam.init(len);
		init(s, len);
		for(int i = 0; i < len; ++i)
			sam.add(s[i] - '0', i);
		for(int i = 0; i <= sam.tot; ++i)
		{
			if(sam.fa[i] != -1)
			{
				sam.nxt[sam.fa[i]].push_back(i);
				sam.min[i] = sam.max[sam.fa[i]] + 1;
			}
			else
				sam.min[i] = 0;
		}
		static vector<int> q;
		q.clear();
		for(int i = 0; i <= sam.tot; ++i)
			if(sam.R[i] != -1)
				q.push_back(i);
		for(int i = 0; i < q.size(); ++i)
		{
			int cur = q[i];
			while(cur != -1)
			{
				sam.R[cur] = sam.R[q[i]];
				sam.cnt[cur]++;
				cur = sam.fa[cur];
			}
		}
		dfsSolve(0, 0, 0);
		for(int i = 0; i < k; ++i)
			printf("%d%c", ans[i], i + 1 == k ? '\n' : ' ');
	}
	return 0;
}
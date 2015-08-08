#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

char s[1000000];

class TrieNode
{
public:
	TrieNode *nxt[26];
	int type;
	vector<int> id[2];
	void init()
	{
		id[0].clear(), id[1].clear();
		type = 0;
		for(int i = 0; i < 26; ++i)
			nxt[i] = NULL;
	}
};

TrieNode t[1000000];

TrieNode *root;
int tot;

int dep[1000000];

TrieNode* newNode()
{
	TrieNode *ret = &t[tot++];
	ret -> init();
	return ret;
}

void insert(char *s, int len, int ty, int id)
{
	TrieNode *cur = root;
	dep[root - t] = 0;
	for(int i = 0; i < len; ++i)
	{
		int nxt = s[i] - 'a';
		if(cur -> nxt[nxt] == NULL)
			cur -> nxt[nxt] = newNode();
		dep[(cur -> nxt[nxt]) - t] = i + 1;
		cur = cur -> nxt[nxt];
	}
	cur -> type |= (1 << ty);
	cur -> id[ty].push_back(id);
}

vector<pair<int, int> > ans;

int res[1000000];
TrieNode *fa[1000000];

void solve()
{
	static TrieNode* q[1000000];
	int l, r;
	l = r = -1;
	q[++r] = root;
	while(l < r)
	{
		TrieNode *cur = q[++l];
		for(int i = 0; i < 26; ++i)
		{
			if(cur -> nxt[i])
			{
				q[++r] = cur -> nxt[i];
				fa[cur -> nxt[i] - t] = cur;
			}
		}
	}
	for(int i = r; i >= 0; --i)
	{
		vector<int> r1, r2;
		int cc = min((q[i] -> id[0]).size(), (q[i] -> id[1]).size());
		res[q[i] - t] += cc * dep[q[i] - t];
		if(fa[q[i] - t] != NULL)
		res[fa[q[i] - t] - t] += res[q[i] - t];
		for(int j = 0; j < cc; ++j)
			ans.push_back(make_pair(q[i] -> id[0][j], q[i] -> id[1][j]));
		if((q[i] -> id[0]).size() > cc)
			for(int j = cc; j < (q[i] -> id[0]).size(); ++j)
				fa[q[i] - t] -> id[0].push_back(q[i] -> id[0][j]);
		else
			for(int j = cc; j < (q[i] -> id[1]).size(); ++j)
				fa[q[i] - t] -> id[1].push_back(q[i] -> id[1][j]);
	}
	printf("%d\n", res[root - t]);
	for(int i = 0; i < ans.size(); ++i)
		printf("%d %d\n", ans[i].first, ans[i].second);
}

int main()
{
	ans.clear();
	ans.resize(100000 + 10);
	ans.clear();
	int n;
	tot = 0;
	root = newNode();
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%s", s);
		insert(s, strlen(s), 0, i + 1);
	}
	for(int i = 0; i < n; ++i)
	{
		scanf("%s", s);
		insert(s, strlen(s), 1, i + 1);
	}
	solve();
	return 0;
}

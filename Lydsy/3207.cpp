#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

map<vector<int>, int> mapping;

const int Maxn = 200000;
int a[Maxn];
int hash[Maxn];

const int MaxNode = 200000 * 20;
 
class Node
{
public:
	int l, r, val;
	Node *lch, *rch;
};

Node t[MaxNode], *rt[Maxn];

class SegTree
{
public:
	int tot;
	Node* newNode()
	{
		Node *ret = &t[tot++];
		ret -> l = ret -> r = -1;
		ret -> val = 0;
		ret -> lch = ret -> rch = 0;
		return ret;
	}
	void insert(Node *pre, Node* &cur, int v, int L, int R)
	{
		cur = newNode();
		if(pre != NULL) *cur = *pre;
		cur -> l = L, cur -> r = R;
		if(L == R)
		{
			cur -> val++;
			return;
		}
		int mid = (L + R) >> 1;
		if(v <= mid)
			insert(pre ? pre -> lch : NULL, cur -> lch, v, L, mid);
		else
			insert(pre ? pre -> rch : NULL, cur -> rch, v, mid + 1, R);
	}
	void Build(int *arr, int n)
	{
		tot = 0;
		rt[0] = NULL;
		for(int i = 1; i <= n; ++i)
			insert(rt[i - 1], rt[i], arr[i], 0, Maxn);
	}
	int query(Node *x, int val)
	{
		if(x == NULL) return 0;
		if(x -> l == x -> r)
			return x -> val;
		else
		{
			int mid = (x -> l + x -> r) >> 1;
			if(val <= mid)
				return query(x -> lch, val);
			else
				return query(x -> rch, val);
		}
	}
	int query(int pos, int val)
	{
		return query(rt[pos], val);
	}
	bool query(int L, int R, int val)
	{
	//	printf("%d %d\n", L, R);
		return query(R, val) - query(L - 1, val) > 0;
	}
}st;

int main()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for(int i = 1; i + k - 1 <= n; ++i)
	{
		vector<int> cur;
		for(int j = 0; j < k; ++j)
			cur.push_back(a[i + j]);
		mapping[cur] = 1;
	}
	int tot = 0;
	for(map<vector<int>, int>::iterator i = mapping.begin(); i != mapping.end(); i++)
		i -> second = tot++;
	for(int i = 1; i + k - 1 <= n; ++i)
	{
		vector<int> cur;
		for(int j = 0; j < k; ++j)
			cur.push_back(a[i + j]);
		hash[i] = mapping[cur];
	}
	if(n >= k)
		st.Build(hash, n - k + 1);
	for(int i = 0; i < m; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		vector<int> c;
		c.resize(k);
		for(int j = 0; j < k; ++j)
			scanf("%d", &c[j]);
		if(mapping.count(c) == 0)
			printf("Yes\n");
		else
		{
			y = min(n - k + 1, y);
			if(y < x)
				printf("Yes\n");
			else
				printf("%s\n", st.query(x, y, mapping[c]) ? "No" : "Yes");
		}
	}
	return 0;
}
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

const int Maxn = 20010 * 2;
const int MaxNode = Maxn * 20;
const int inf = 0x3f3f3f3f;

class Node
{
public:
	int sum, lsum, rsum, l, r, val;
	Node *lch, *rch;
};
Node *rt[Maxn], t[MaxNode];

class Segment
{
public:
	int tot;
	Node* newNode()
	{
		Node* ret = &t[tot++];
		ret -> sum = ret -> val = 0;
		ret -> lch = ret -> rch = NULL;
		ret -> l = ret -> r = -1;
		ret -> lsum = ret -> rsum = -inf;
		return ret;
	}
	void update(Node *x)
	{
		Node *ret = x;
		ret -> sum = ret -> val;
		ret -> lsum = ret -> rsum = -inf;
		if(ret -> lch)
		{
			ret -> sum += ret -> lch -> sum;
			ret -> lsum = max(ret -> lsum, ret -> lch -> lsum);
			if(ret -> rch)
				ret -> rsum = max(ret -> rsum, ret -> rch -> sum + ret -> lch -> rsum);
		}
		if(ret -> rch)
		{
			ret -> sum += ret -> rch -> sum;
			ret -> rsum = max(ret -> rsum, ret -> rch -> rsum);
			if(ret -> lch)
				ret -> lsum = max(ret -> lsum, ret -> lch -> sum + ret -> rch -> lsum);
		}
	}
	void Build(int L, int R, int *arr, Node* &cur)
	{
		cur = newNode();
		cur -> l = L, cur -> r = R;
		if(L == R)
		{
			cur -> val = cur -> sum = cur -> lsum = cur -> rsum = arr[L];
		}
		else
		{
			int mid = (L + R) >> 1;
			Build(L, mid, arr, cur -> lch);
			Build(mid + 1, R, arr, cur -> rch);
			update(cur);
		}
	}
	void init(int x, int *a, int n)
	{
		tot = 0;
		Build(0, n - 1, a, rt[0]);
	}
	void change(int pos, int val, Node *preVer, Node* &curVer)
	{
		curVer = newNode();
		*curVer = *preVer;
		if(curVer -> l == curVer -> r)
		{
			curVer -> val = curVer -> sum = curVer -> lsum = curVer -> rsum = val;
		}
		else
		{
			int mid = curVer -> l + curVer -> r;
			mid >>= 1;
			if(pos <= mid) change(pos, val, preVer -> lch, curVer -> lch);
			else change(pos, val, preVer -> rch, curVer -> rch);
			update(curVer);
		}
	}
	Node merge(const Node &a, const Node &b)
	{
		Node ret;
		ret.sum = a.sum + b.sum;
		ret.lsum = max(a.lsum, a.sum + b.lsum);
		ret.rsum = max(b.rsum, a.rsum + b.sum);
		return ret;
	}
	Node query(int l, int r, Node* cur)
	{
		if(l > r)
		{
			Node x;
			x.sum = x.rsum = x.lsum = 0;
			return x;
		}
		if(cur -> l == l && cur -> r == r)
			return *cur;
		else
		{
			int mid = (cur -> l + cur -> r) >> 1;
			if(r <= mid) return query(l, r, cur -> lch);
			else if(l > mid) return query(l, r, cur -> rch);
			else
			{
				Node a, b;
				a = query(l, mid, cur -> lch), b = query(mid + 1, r, cur -> rch);
				return merge(a, b);
			}
		}
	}
}st;

long long a[Maxn];
int finalVer[Maxn];

map<long long, long long> mapping, remap, mapLoc;

bool check(int x, int *q)
{
	int s = st.query(q[0], q[1], rt[finalVer[x]]).rsum + st.query(q[2], q[3], rt[finalVer[x]]).lsum + st.query(q[1] + 1, q[2] - 1, rt[finalVer[x]]).sum;
	return s < 0;
}

int main()
{
	int n;
	while(scanf("%d", &n) == 1)
	{
		mapping.clear();
		for(int i = 0; i < n; ++i)
		{
			scanf("%lld", &a[i]);
			a[i] = (a[i] * 100000) + i;
			mapping[a[i]] = 1;
		}
		int tot = 0;
		for(map<long long, long long>::iterator i = mapping.begin(); i != mapping.end(); i++)
		{
			i -> second = tot;
			remap[tot++] = i -> first;
		}
		for(int i = 0; i < n; ++i)
		{
			a[i] = mapping[a[i]];
			mapLoc[a[i]] = i;
		}
		static int b[Maxn];
		int prePos;
		tot = 0;
		for(map<long long, long long>::iterator i = mapping.begin(); i != mapping.end(); i++)
		{
			if(i == mapping.begin())
			{
				for(int j = 0; j < n; ++j)
					b[j] = 1;
				st.init(i -> second, b, n);
				prePos = mapLoc[i -> second];
				finalVer[i -> second] = tot;
				tot++;
			}
			else
			{
				b[prePos] = -1;
				st.change(mapLoc[i -> second], 1, rt[tot - 1], rt[tot]);
				tot++;
				st.change(prePos, -1, rt[tot - 1], rt[tot]);
				finalVer[i -> second] = tot;
				tot++;
				prePos = mapLoc[i -> second];
			}
		}
		int q, x = 0;
		scanf("%d", &q);
		for(int i = 0; i < q; ++i)
		{
			int qu[4];
			for(int j = 0; j < 4; ++j)
				scanf("%d", qu + j);//, qu[j] = (x + qu[j]) % n;
			#ifdef ONLINE_JUDGE
			for(int j = 0; j < 4; ++j)
				qu[j] = (qu[j] + x) % n;
			#endif
			sort(qu, qu + 4);
			int l = 0, r = n - 1;
			while(l <= r)
			{
				int mid = (l + r) >> 1;
				if(check(mid, qu))
					r = mid - 1;
				else
					l = mid + 1;
			}
			x = (remap[r] / 100000);
			printf("%d\n", x);
		}
	}
	return 0;
}
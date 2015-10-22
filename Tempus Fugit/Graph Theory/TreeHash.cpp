#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

const int mm = 1051697, p = 1e9 + 9, q = 1e9 + 7;
const int N = 100000 + 10;
vector<int> vec[N];
int n, size[N], mark[N], deg[N], father[N];
long long f[N], g[N], rtp[N], rtq[N];
map<pair<long long, long long>, int> mp;

struct Node {
    int a, b, v;
    Node() {}
    Node(int _a, int _b, int _v) {
        a = _a, b = _b, v = _v;
    }
    bool operator < (const Node &rhs) const {
        if (a == rhs.a )
            return b < rhs.b;
        return a < rhs.a;
    }
};

struct HashNode {
    int pos;
    long long val1, val2;
    HashNode() {}
    HashNode(int _pos, long long _val1, long long _val2) {
        pos = _pos;
        val1 = _val1;
        val2 = _val2;
    }
    bool operator < (const HashNode &rhs) const {
        if (val1 == rhs.val1)
            return val2 < rhs.val2;
        return val1 < rhs.val1;
    }
};
	
void hashwork(int u)
{
    vector<Node> data;
    size[u] = 1;
    for (int i = 0; i < (int)vec[u].size(); ++i) {
        int v = vec[u][i];
        hashwork(v);
        data.push_back(Node(f[v], g[v], size[v]));
        size[u] += size[v];
    }
    data.push_back(Node(1, 1, size[u]));
    sort(data.begin(), data.end());

    int len = 0;
    f[u] = 1;
    for (int i = 0; i < (int)data.size(); ++i) {
        f[u] = ((f[u] * data[i].a) % p * rtp[len]) % p;
        g[u] = ((g[u] * data[i].b) % q + rtq[len]) % q;
        len += data[i].v;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    rtp[0] = rtq[0] = 1;
    for (int i = 1; i < N; ++i) {
        rtp[i] = (rtp[i - 1] * mm) % p;
        rtq[i] = (rtq[i - 1] * mm) % q;
    }

    queue<int> que;
    cin >> n;
    for (int v = 2; v <= n; ++v) {
        int u;
        cin >> u;
        vec[u].push_back(v);
        father[v] = u;
        deg[u]++;
    }
    memset(size, 0, sizeof(size));
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 0) 
            que.push(i);
    while (!que.empty()) {
        int u = que.front();
        //cout << u << endl;
        que.pop();

        deg[father[u]]--;
        if (deg[father[u]] == 0) que.push(father[u]);

        vector<Node> data;
        size[u] = 1;
        for (int i = 0; i < (int)vec[u].size(); ++i) {
            int v = vec[u][i];
            //hashwork(v);
            data.push_back(Node(f[v], g[v], size[v]));
            size[u] += size[v];
        }
        data.push_back(Node(1, 1, size[u]));
        sort(data.begin(), data.end());
		
        int len = 0;
        f[u] = 1;
        for (int i = 0; i < (int)data.size(); ++i) {
            f[u] = ((f[u] * data[i].a) % p * rtp[len]) % p;
            g[u] = ((g[u] * data[i].b) % q + rtq[len]) % q;
            len += data[i].v;
        }
    }
	
    //hashwork(1);
    /*
      vector<HashNode> ans;
      for (int i = 1; i <= n; ++i) {
      ans.push_back(HashNode(i, f[i], g[i]));
      }
      sort(ans.begin(), ans.end());
      int tot = 0;
      for (int i = 0, j; i < (int)ans.size(); i = j) {
      ++tot;
      for (j = i; j < (int)ans.size() && (ans[j].val1 == ans[i].val1 && ans[j].val2 == ans[i].val2); ++j) 
			mark[ans[j].pos] = tot;
      }
    */
    int tot = 0;
    for (int i = 1; i <= n; ++i) {
        pair<long long, long long> pr = make_pair(f[i], g[i]);
        if (mp.count(pr) == 0) {
            mp[pr] = ++tot;
            mark[i] = tot;
        } else {
            mark[i] = mp[pr];
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << mark[i];
        if (i == n) cout << endl;
        else cout << " ";
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>

using namespace std;

const int MAXN = 10000 + 10;

char str[MAXN], a[MAXN];
int n;
long long ans;
int r[MAXN], maxd, idx;

const int mm = 1051697, p = 1e9 + 7, q = 1e9 + 9;

class HashNode
{
public:
	long long h1, h2;
	void init()
	{
		h1 = h2 = 0;
	}
};

HashNode h[MAXN * 2];
long long powp[100000], powq[100000];

void initHash(int len)
{
	powp[0] = powq[0] = 1;
	for(int i = 1; i < 100000; ++i)
		powp[i] = powp[i - 1] * mm % p, powq[i] = powq[i - 1] * mm % q;
	h[0].init();
	for(int i = 1; i <= len; ++i)
	{
		h[i].h1 = powp[i] * a[i] % p + h[i - 1].h1;
		h[i].h1 %= p;
		h[i].h2 = powq[i] * a[i] % q + h[i - 1].h2;
		h[i].h2 %= q;
	}
}

map<pair<long long, long long>, bool> CountHash;

pair<long long, long long> getHash(int l, int r)
{
//	cout << l << " " << r << endl;
	long long res1, res2;
	res1 = res2 = 0;
	res1 = h[r].h1 - h[l - 1].h1;
	res2 = h[r].h2 - h[l - 1].h2;
	res1 %= p, res2 %= q;
	if(res1 < 0) res1 += p;
	if(res2 < 0) res2 += q;
	return make_pair(res1 * powp[50000 - l] % p, res2 * powq[50000 - l] % q);
}

bool singleCount[300];

int main() {
	CountHash.clear();
	scanf("%s", str + 1);
	n = strlen(str + 1);
	
	int single = 0;
	for (int i = 1; i <= n; ++i) {
		a[i * 2] = str[i];
		if(!singleCount[str[i]])
		{
			singleCount[str[i]] = true;
			single++;
		}
		a[i * 2 + 1] = '#';
	}
	a[1] = '#';
	n = 2 * n + 1;
	r[1] = 1;
	maxd = 0, idx = -1;
	a[n + 1] = '?';
	initHash(n);
	for (int i = 1; i <= n; ++i) {
		if (maxd > i)
			r[i] = min(maxd - i, r[idx * 2 - i]);
		else
			r[i] = 1;
		while (a[i + r[i]] == a[i - r[i]]) {
	
			if (a[i + r[i]] != '#') {
				//cout << i / 2 << endl;
				CountHash[getHash(i - r[i], i + r[i])] = true;
				//++ans;
			}
			++r[i];
		}
		if (i + r[i] > maxd) {
			maxd = i + r[i];
			idx = i;
		}
	}
//	for (int i = 1; i <= n; ++i)
//		cout << r[i] << ' ';
//	cout << endl;
	
	cout << CountHash.size() + single << endl;

	return 0;
}

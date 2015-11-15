namespace SuffixArrayDoubling {
	int wa[MAXN], wb[MAXN], wv[MAXN], ws[MAXN];
	int cmp(int *r, int a, int b, int l) { return r[a] == r[b] && r[a + l] == r[b + l]; }
	void da(int *r, int *sa, int n, int m) {
		int i, j, p, *x = wa, *y = wb, *t; 
		for (i = 0; i < m; i++) ws[i] = 0;
		for (i = 0; i < n; i++) ws[x[i] = r[i]]++;
		for (i = 1; i < m; i++) ws[i] += ws[i - 1];
		for (i = n - 1; i >= 0; i--) sa[--ws[x[i]]] = i;
		for (j = 1, p = 1; p < n; j *= 2, m = p) {
			for (p = 0, i = n - j; i < n; i++) y[p++] = i;
			for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
			for (i = 0; i < n; i++) wv[i] = x[y[i]];
			for (i = 0; i < m; i++) ws[i] = 0;
			for (i = 0; i < n; i++) ws[wv[i]]++;
			for (i = 1; i < m; i++) ws[i] += ws[i - 1];
			for (i = n - 1; i >= 0; i--) sa[--ws[wv[i]]] = y[i];
			for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
				x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
}}}
namespace CalcHeight {
	int rank[MAXN], height[MAXN];
	void calheight(int *r, int *sa, int n) { 
		int i, j, k = 0; for (i = 1; i <= n; i++) rank[sa[i]] = i;
		for (i = 0; i < n; height[rank[i++]] = k)
			for (k ? k-- : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; k++);
}
	void init(int len)
	{
		for(int i = 0; i <= len + 10; ++i)
			rank[i] = height[i] = 0;
	}
}
//Sample
int r[MAXN]; char s[MAXN];
int main()
{
	int len;
	scanf("%s", s);
	len = strlen(s);
	for(int i = 0; i < len; ++i) r[i] = s[i] - 'a' + 1;
	r[len] = 0;
	SuffixArrayDoubling::da(r, sa, n + 1, 30);
	CalcHeight::calheight(r, sa, n);
	//Then the value of sa[0~len-1] is 1 ~ n, so init RMQ carefully(1~n not 0~n-1)
	return 0;
}
}

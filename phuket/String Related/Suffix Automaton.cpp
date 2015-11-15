struct SAM {
	int in[Maxn * 2 + 1][Sigma], fa[Maxn * 2 + 1], max[Maxn * 2 + 1], tot, last;
	void init(int n) {
		tot = last = 0;
		for(int i = 0; i <= 2 * n + 1; ++i)
			memset(in[i], -1, sizeof in[i]), fa[i] = -1;
	}
	void add(int x) {
		int v = last; ++tot, last = tot, max[last] = max[v] + 1;
		while(v != -1 && in[v][x] == -1) in[v][x] = last, v = fa[v];
		if(v == -1) { fa[last] = 0; return; }
		int p = in[v][x];
		if(max[p] == max[v] + 1) fa[last] = p;
		else {
			int np = ++tot;
			max[np] = max[v] + 1; fa[np] = fa[p], fa[p] = np, fa[last] = np;
			while(v != -1 && in[v][x] == p) in[v][x] = np, v = fa[v];
			memcpy(in[np], in[p], sizeof in[p]);
}}};

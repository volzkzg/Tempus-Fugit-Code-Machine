struct MinCostFlow {
	int e[M], succ[M], last[N], val[M], cost[M], sum, dis[N], visit[N], slack[N];
	int source, target, totFlow, totCost;
	void init(int n) {
		for (int i = 1; i <= n; i++) last[i] = 0;
		sum = 1;
	}
	void add(int a, int b, int c, int d) {
		e[++sum] = b, succ[sum] = last[a], last[a] = sum;
		e[++sum] = a, succ[sum] = last[b], last[b] = sum;
		val[sum - 1] = c, val[sum] = 0;
		cost[sum - 1] = d, cost[sum] = -d;
	}
	int modlable() {
		int delta = INF;
		for (int i = 1; i <= target; i++) {
			if (!visit[i] && slack[i] < delta) delta = slack[i];
			slack[i] = INF;
		}
		if (delta == INF) return 1;
		for (int i = 1; i <= target; i++) if (visit[i])
			dis[i] += delta;
		return 0;
	}

	int dfs(int x, int flow) {
		if (x == target) {
			totFlow += flow;
			totCost += flow * (dis[source] - dis[target]);
			return flow;
		}
		visit[x] = 1; int left = flow;
		for (int i = last[x]; i; i = succ[i]) {
			if (val[i] > 0 && !visit[e[i]]) {
				int y = e[i];
				if (dis[y] + cost[i] == dis[x]) {
					int delta = dfs(y, min(left, val[i]));
					val[i] -= delta, val[i ^ 1] += delta;
					left -= delta;
					if (!left) {
						visit[x] = 0;
						return flow;
					}
				} else slack[y] = min(slack[y], dis[y] + cost[i] - dis[x]);
			}
		}
		return flow - left;
	}
	pair <int, int> minCost() {
		totFlow = 0, totCost = 0;
		fill(dis + 1, dis + target + 1, 0);
		do {
			do {
				fill(visit + 1, visit + target + 1, 0);
			} while (dfs(source, INF));
		} while (!modlable());
		return make_pair(totFlow, totCost);
	}
} mcf;
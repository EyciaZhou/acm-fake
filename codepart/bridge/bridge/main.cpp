vector<int> g[10005];
int vis[10005];
int pre[10005];
int anc[10005];

void dfs(int cur, int father, int dep) { // vertex: 0 ~ n-1
	vis[cur] = 1;
	pre[cur] = anc[cur] = dep;
	for (int i = 0; i < g[cur].size(); i++) {
		if (g[cur][i] != father && 1 == vis[g[cur][i]]) {
			if (pre[g[cur][i]] < anc[cur])
				anc[cur] = pre[g[cur][i]];//back edge
		}
		if (0 == vis[g[cur][i]]) { //tree edge
			dfs(g[cur][i], cur, dep+1);
			if (anc[g[cur][i]] < anc[cur])
				anc[cur] = anc[g[cur][i]];
			if (anc[g[cur][i]] > pre[cur]) {
				
				// cur to g[cur][i] is bridge
				uni(cur, g[cur][i]);
			}
		}
	}
	vis[cur] = 2;
}

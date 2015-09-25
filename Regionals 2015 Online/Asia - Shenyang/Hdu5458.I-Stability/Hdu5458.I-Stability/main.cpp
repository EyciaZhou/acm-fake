//
//  main.cpp
//  Hdu5458.I-Stability
//
//  Created by eycia on 24/9/15.
//  Copyright © 2015 eycia. All rights reserved.
//

#include <set>
#include <map>
#include <list>
#include <tuple>
#include <ratio>
#include <cmath>
#include <queue>
#include <stack>
#include <deque>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> g[40005];

map<pair<int, int>, int > dd;

vector<pair<int, int> > i1;

vector<tuple<int, int, int> > qu;

int vis[40005];
int pre[40005];
int anc[40005];

int f[40005];

int getf(int c) {
	return f[c] == c ? c : f[c] = getf(f[c]);
}

void uni(int l, int r) {
	int f1 = getf(l), f2 = getf(r);
	if (f1 != f2) {
		f[f1] = f2;
	}
}

void dfs(int cur, int father, int dep) { // vertex: 0 ~ n-1
	vis[cur] = 1;
	pre[cur] = anc[cur] = dep;
	for (int i = 0; i < g[cur].size(); i++) {
		if (g[cur][i] != father && 1 == vis[g[cur][i]]) {
			if (pre[g[cur][i]] < anc[cur]) {
				anc[cur] = pre[g[cur][i]];//back edge
				uni(cur, g[cur][i]);
			}
		}
		if (0 == vis[g[cur][i]]) { //tree edge
			dfs(g[cur][i], cur, dep+1);
			if (anc[g[cur][i]] < anc[cur]) {
				anc[cur] = anc[g[cur][i]];
				uni(cur, g[cur][i]);
			}
			if (anc[g[cur][i]] > pre[cur]) {
				// cur to g[cur][i] is bridge
				//uni(cur, g[cur][i]);
			}
		}
	}
	vis[cur] = 2;
}

namespace segtree {
	int laz[200005];
	int sum[200005];
	int n;
	
#define lc(a) (a << 1)
#define rc(a) ((a<<1) | 1)
	
	void build(int t, int l, int r) {
		if (l > r) return ;
		if (l == r) {
			laz[t] = 0;
			sum[t] = 1;
			return ;
		}
		int mi = (l+r) / 2;
		build(lc(t), l, mi);
		build(rc(t), mi+1, r);
		laz[t] = 0;
		sum[t] = r-l+1;
	}
	
	void init(int k) {
		build(1, 1, k);
		n = k;
	}
	
	void inline push_down(int t) {
		if (laz[t]) {
			laz[lc(t)] = laz[rc(t)] = 1;
			laz[t] = 0;
			
			sum[lc(t)] = sum[rc(t)] = 0;
		}
	}
	
	void inline update(int t) {
		sum[t] = sum[lc(t)] + sum[rc(t)];
	}
	
	void _m(int t, int l, int r, int ll, int rr) {
		if (ll > rr) return ;
		if (ll == rr) {
			sum[t] = laz[t] = 0;
			return ;
		}
		if (sum[t] == 0) return;
		
		if (l == ll && r == rr) {
			sum[t] = 0;
			laz[t] = 1;
		}
		
		push_down(t);
		
		int mi = (ll+rr) / 2;
		if (r <= mi) {
			_m(lc(t), l, r, ll, mi);
		} else if (l > mi) {
			_m(rc(t), l, r, mi+1, rr);
		} else {
			_m(lc(t), l, mi, ll, mi);
			_m(rc(t), mi+1, r, mi+1, rr);
		}
		
		update(t);
	}
	
	int _q(int t, int l, int r, int ll, int rr) {
		if (ll > rr) return 0;
		if (ll == rr) {
			return sum[t];
		}
		if (sum[t] == 0) return 0;
		
		if (l == ll && r == rr) {
			return sum[t];
		}
		
		push_down(t);
		
		int mi = (ll+rr) / 2;
		if (r <= mi) {
			return _q(lc(t), l, r, ll, mi);
		} else if (l > mi) {
			return _q(rc(t), l, r, mi+1, rr);
		} else {
			return _q(lc(t), l, mi, ll, mi) + _q(rc(t), mi+1, r, mi+1, rr);
		}
	}
	
	int query(int t, int l, int r) {
		return _q(t, l, r, 1, n);
	}
	
	void modify(int t, int l, int r) {
		return _m(t, l, r, 1, n);
	}
	
	
}

namespace slpf {
	vector<int> g2[40005];
	vector<int> g3[40005];
	const int N = 40005;
	int mem = 1;
	int siz[N], dep[N], fa[N], hson[N];
	int top[N], w[N], w2[N];
	int qz[N];
	
	void gg(int n, int fa) {
		for (int i = 0; i < g2[n].size(); i++) {
			if (g2[n][i] != fa) {
				g3[n].push_back(g2[n][i]);
				gg(g2[n][i], n);
			}
		}
	}
	
	void gentree(int n) {
		for (int i = 1; i <= n; i++) {
			getf(i);
		}
		
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < g[i].size(); j++) {
				if (f[i] != f[g[i][j]]) {
					g2[f[i]].push_back(f[g[i][j]]);
				}
			}
		}
		
		gg(getf(1), 0);
	}
	
	int dfs1(int n, int f) {
		dep[n] = dep[f]+1;
		fa[n] = f;
		int tot = 0;
		int tmp, p = 0, k = 0;
		if (g3[n].size() > 0) {
			for (int i = 0; i < g3[n].size(); i++) {
				tmp = dfs1(g3[n][i], n);
				if (tmp > k) {
					k = tmp;
					p = g3[n][i];
				}
				tot += tmp;
			}
		}
		hson[n] = p;
		return siz[n] = tot+1;
	}
	
	void dfs2(int n, int fa) {
		w[n] = ++mem;
		w2[mem] = n;
		
		top[n] = fa;
		if (g3[n].size() > 0) {
			dfs2(hson[n], fa);
			for (int i = 0; i < g3[n].size(); i++) {
				if (g3[n][i] != hson[n]) {
					dfs2(g3[n][i], g3[n][i]);
				}
			}
		}
	}
	
	int lca(int le, int ri) {
		int f1 = top[le], f2 = top[ri];
		while (f1 != f2 ) {
			if (dep[f1] < dep[f2]) {
				swap(f1, f2); swap(le, ri);
			}
			le = fa[f1]; f1 = top[le];
		}
		if (le == ri) return le;
		if (dep[le] > dep[ri]) swap(le, ri);
		return le;
	}
	
	long long query(int le, int ri) {
		int f1 = top[le], f2 =top[ri];
		long long tmp = 0;
		while (f1 != f2) {
			if (dep[f1] < dep[f2]) {
				swap(f1, f2); swap(le, ri);
			}
			tmp += segtree::query(1, w[f1], w[le]);
			
			le = fa[f1]; f1 = top[le];
		}
		if (le == ri) {return tmp;}
		if (dep[le] > dep[ri]) swap(le, ri);
		return tmp + segtree::query(1, w[le]+1, w[ri]);
	}
	
	void modify(int le, int ri) {
		int f1 = top[le], f2 =top[ri];
		while (f1 != f2) {
			if (dep[f1] < dep[f2]) {
				swap(f1, f2); swap(le, ri);
			}
			
			segtree::modify(1, w[f1], w[le]);
			
			le = fa[f1]; f1 = top[le];
		}
		if (le == ri) {return ;}
		if (dep[le] > dep[ri]) swap(le, ri);
		return segtree::modify(1, w[le]+1, w[ri]);
	}
	
	void init(int n) {
		for (int i = 0; i < N; i++) {
			g2[i].clear();
			g3[i].clear();
		}
		mem = 0;
		
		gentree(n);
		dfs1(getf(1), 0);
		dfs2(getf(1), getf(1));
		
		segtree::init(mem);
	}
}


vector<int> ans;

set<pair<int, int> > cb;

void work() {
	for (int i = 0; i < 40005; i++) {
		f[i] = i;
	}
	for (int i = 0; i < 40005; i++) {
		g[i].clear();
	}
	
	cb.clear();
	ans.clear();
	dd.clear();
	i1.clear();
	qu.clear();
	
	int n, m, q, u, v, a, b, c;
	scanf("%d %d %d", &n, &m, &q);
	
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		if (u > v) swap(u, v);
		i1.push_back(make_pair(u, v));
	}
	for (int i = 0; i < q; i++) {
		scanf("%d %d %d", &a, &b, &c);
		if (a == 1) {
			if (b > c) swap(b, c);
			dd[make_pair(b, c)]++;
		}
		qu.push_back(make_tuple(a, b, c));
	}
	
	for (int i = 0; i < m; i++) {
		if (dd[i1[i]] == 0) {
			if (cb.find(i1[i]) == cb.end()) {
				if (i1[i].first == i1[i].second) continue;
				cb.insert(i1[i]);
				g[i1[i].first].push_back(i1[i].second);
				g[i1[i].second].push_back(i1[i].first);
			} else {
				uni(i1[i].first, i1[i].second);
			}
		} else {
			dd[i1[i]]--;
		}
	}
	
	memset(vis, 0, sizeof(vis));
	dfs(1, -1, 0);
	
	slpf::init(n);
	
	for (int i = q-1 ; i >= 0; i--) {
		int a = get<0>(qu[i]), b = get<1>(qu[i]), c = get<2>(qu[i]);
		if (a == 1) {
			if (getf(b) == getf(c)) continue;
			slpf::modify(getf(b), getf(c));
		} else {
			if (getf(b) == getf(c)) {
				ans.push_back(0);
			} else {
				ans.push_back(slpf::query(getf(b), getf(c)));
			}
		}
	}
	
	int s = ans.size();
	for (int i = s-1; i >= 0; i--) {
		printf("%d\n", ans[i]);
	}
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int ff = 1; ff <= t; ff++) {
		printf("Case #%d:\n", ff);
		work();
	}
}
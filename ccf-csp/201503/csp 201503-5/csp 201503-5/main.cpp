//
//  main.cpp
//  csp 201503-5
//
//  Created by eycia on 4/9/15.
//  Copyright (c) 2015 eycia. All rights reserved.
//

#include <set>
#include <map>
#include <list>
//#include <tuple>
//#include <ratio>
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

struct edge {
	int u, v, w;
}e[200005];

int wa[100005];

vector<int> g2[100005];
vector<int> g[100005];
int back[100005];

void gen_tree(int n, int fa) {
	for (int i = 0; i < g2[n].size(); i++) {
		if (e[g2[n][i]].v != fa) {
			g[n].push_back(g2[n][i]);
			back[e[g2[n][i]].v] = g2[n][i];
			gen_tree(e[g2[n][i]].v, n);
		}
	}
}

long long qq[100005];
int mi[100005];
int mem = 0;
int siz[100005], dep[100005], fa[100005], hson[100005];
int top[100005], w[100005], w2[100005];

int dfs1(int n, int f) {
	dep[n] = dep[f]+1;
	fa[n] = f;
	int tot = 0;
	int tmp, p = 0, k = 0;
	if (g[n].size() > 0) {
		for (int i = 0; i < g[n].size(); i++) {
			tmp = dfs1(e[g[n][i]].v, n);
			if (tmp > k) {
				k = tmp;
				p = e[g[n][i]].v;
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
	qq[mem] = e[back[n]].w;
	mi[mem] = wa[n];
	top[n] = fa;
	if (g[n].size() > 0) {
		dfs2(hson[n], fa);
		for (int i = 0; i < g[n].size(); i++) {
			if (e[g[n][i]].v != hson[n]) {
				dfs2(e[g[n][i]].v, e[g[n][i]].v);
			}
		}
	}
}

struct {
	vector<vector<int> > k;
	int *aa;
	void init(int *a, int len) {
		aa = a;
		int mn = len;
		int ml = (int)(log(mn) / log(2) + 5);
		for (int i = 0; i < ml; i++) {
			k.push_back(vector<int>());
		}
		for (int i = 0; i < mn; i++) {
			k[0].push_back(i);
		}
		for (int j = 1; j < ml; j++) {
			for (int i = 0; i < mn; i++) {
				
				if ((1 << (j-1))+i < mn) {
					if (a[k[j-1][i]] < a[k[j-1][(1 << (j-1))+i]]) {
						k[j].push_back(k[j-1][i]);
					} else {
						k[j].push_back(k[j-1][(1 << (j-1))+i]);
					}
				} else {
					k[j].push_back(k[j-1][i]);
				}
			}
		}
	}
	
	int query(int l, int r) {
		if (l > r) swap(r, l);
		int len = r - l + 1;
		int c = int(log(len) / log(2));
		if (aa[k[c][l]] < aa[k[c][r-(1<<c)+1]]) {
			return k[c][l];
		}
		return k[c][r-(1<<c)+1];
	}
} rmq_st;

int ca;

long long sum(int le, int ri) {
	int f1 = top[le], f2 =top[ri];
	long long tmp = 0;
	while (f1 != f2) {
		if (dep[f1] < dep[f2]) {
			swap(f1, f2); swap(le, ri);
		}
		tmp += qq[w[le]] - qq[w[f1]-1];
		
		le = fa[f1]; f1 = top[le];
	}
	if (le == ri) {return tmp;}
	if (dep[le] > dep[ri]) swap(le, ri);
	return tmp + qq[w[ri]] - qq[w[le]];
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

int get_mi(int le, int ri) {
	int ca = lca(le, ri);
	if (ri != ca) {
		ri = fa[ri];
		
		int f1 = top[le], f2 = top[ri];
		long long tmp = 0x7fffffff;
		int in = 0;
		while (f1 != f2) {
			if (dep[f1] < dep[f2]) {
				swap(f1, f2); swap(le, ri);
			}
			int tin = rmq_st.query(w[f1], w[le]);
			if (wa[w2[tin]] < tmp) {
				tmp = wa[w2[tin]];
				in = tin;
			}
			le = fa[f1]; f1 = top[le];
		}
		if (dep[le] > dep[ri]) swap(le, ri);
		int tin = rmq_st.query(w[le], w[ri]);
		if (wa[w2[tin]] < tmp) {
			tmp = wa[w2[tin]];
			in = tin;
		}
		return w2[in];
	}
	
	int f1 = top[le], f2 = top[ri];
	long long tmp = 0x7fffffff;
	int in = 0;
	while (f1 != f2 && fa[le] != ca) {
		int tin = rmq_st.query(w[f1], w[le]);
		if (wa[w2[tin]] < tmp) {
			tmp = wa[w2[tin]];
			in = tin;
		}
		le = fa[f1]; f1 = top[le];
	}
	if (le == ri) return w2[in];
	if (fa[le] == ca) {
		if (wa[le] < tmp) {
			tmp = wa[le];
			in = w[le];
		}
	} else {
		int tin = rmq_st.query(w[le], w[hson[ri]]);
		if (wa[w2[tin]] < tmp) {
			tmp = wa[w2[tin]];
			in = tin;
		}
	}
	return w2[in];
}

int main(int argc, const char * argv[]) {
	int n, q, u, v, ww, m=0;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &wa[i]);
	}
	for (int i = 0; i < n-1; i++) {
		scanf("%d %d %d", &u, &v, &ww);
		e[m].u = u; e[m].v = v; e[m].w = ww;
		g2[u].push_back(m++);
		e[m].u = v; e[m].v = u; e[m].w = ww;
		g2[v].push_back(m++);
	}
	//gen tree
	gen_tree(1, 0);
	
	//dec
	dfs1(1, 0);
	dfs2(1, 1);
	
	//gen qzh
	for (int i = 1; i <= mem; i++) qq[i] += qq[i-1];
	//gen rmq
	rmq_st.init(mi, mem+1);
	
	for (int i = 0; i < q; i++) {
		int u, v;
		long long ans = 0;
		scanf("%d %d", &u, &v);
		if (u == v) {
			cout << 0 << endl;
			continue;
		}
		
		//u = w[u]; v = w[v];

		while (true) {
			int step = get_mi(u, v);
			//break; // debug
			long long worth = wa[step];
			long long length = sum(step, v);
			v = step;
			ans += worth * length;
			if (step == u) break;
		}
		printf("%lld\n", ans);
	}
}

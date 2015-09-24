//
//  main.cpp
//  a5
//
//  Created by eycia on 19/9/15.
//  Copyright (c) 2015 eycia. All rights reserved.
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

#define N 200010

vector<int> g[N];
vector<int> g2[N];

int mem = 0;
int siz[N], dep[N], fa[N], hson[N];
int top[N], w[N], w2[N];
int qz[N];

void gen_tree(int n, int fa) {
	for (int i = 0; i < g2[n].size(); i++) {
		if (g2[n][i] != fa) {
			g[n].push_back(g2[n][i]);
			gen_tree(g2[n][i], n);
		}
	}
}

int dfs1(int n, int f) {
	dep[n] = dep[f]+1;
	fa[n] = f;
	int tot = 0;
	int tmp, p = 0, k = 0;
	if (g[n].size() > 0) {
		for (int i = 0; i < g[n].size(); i++) {
			tmp = dfs1(g[n][i], n);
			if (tmp > k) {
				k = tmp;
				p = g[n][i];
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
	if (g[n].size() > 0) {
		dfs2(hson[n], fa);
		for (int i = 0; i < g[n].size(); i++) {
			if (g[n][i] != hson[n]) {
				dfs2(g[n][i], g[n][i]);
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

int work() {
	memset(qz, 0, sizeof(qz));
	
	for (int i = 0; i < N; i++) {
		g[i].clear();
		g2[i].clear();
	}
	int n, m, l, r;
	mem = 0;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n-1; i++) {
		scanf("%d %d", &l, &r);
		g2[l].push_back(r);
		g2[r].push_back(l);
	}
	
	//gen tree
	gen_tree(1, 0);
	
	//dec
	dfs1(1, 0);
	dfs2(1, 1);
	
	for (int i = n-1; i < m; i++) {
		scanf("%d %d", &l, &r);
		int lc = lca(l, r);
		if (lc == l) {
			qz[w[l]]--;
			qz[w[r]]++;
		} else if (lc == r) {
			qz[w[r]]--;
			qz[w[l]]++;
		} else {
			qz[w[l]]++;
			qz[w[r]]++;
			qz[w[lc]]-=2;
		}
	}
	
	for (int i = n; i >= 1; i--) {
		qz[w[fa[w2[i]]]] += qz[i];
	}
	
	int mi = 0x7fffffff;
	
	for (int i = 2; i <= n; i++) {
		mi = min(mi, qz[i]);
	}
	
	return mi+1;
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int ff = 1; ff <= t; ff++) {
		printf("Case #%d: %d\n", ff, work());
	}
}

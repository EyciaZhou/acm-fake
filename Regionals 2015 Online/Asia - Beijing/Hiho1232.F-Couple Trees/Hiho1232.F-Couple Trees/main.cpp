//
//  main.cpp
//  Hiho1232.F-Couple Trees
//
//  Created by eycia on 23/9/15.
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
#include <stddef.h>
using namespace std;

#define N 200005

int n, q;


vector<int> g2[N];


struct slpf {
	vector<int> g[N];
	int mem = 0;
	int siz[N], dep[N], fa[N], hson[N];
	int top[N], w[N], ww[N];
	int qz[N];
	
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
		ww[mem] = n;
		
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
	
	void jump(int &now, int tar) {
		while (now > tar) {
			if (top[now] == now) {
				now = fa[now];
			} else if (top[now] < tar) {
				now = *lower_bound(ww+w[top[now]], ww+w[now]+1, tar);
				if (now != tar) {
					now = fa[now];
				}
			} else {
				now = top[now];
			}
		}
	}
	
} t1, t2;

void work() {
	t1.mem = 0;
	t2.mem = 0;
	
	int tmp;
	for (int i = 0; i <= n; i++) {
		t1.g[i].clear();
		t2.g[i].clear();
	}
	
	for (int i = 2; i <= n; i++) {
		scanf("%d", &tmp);
		t1.g[tmp].push_back(i);
	}
	for (int i = 2; i <= n; i++) {
		scanf("%d", &tmp);
		t2.g[tmp].push_back(i);
	}

	t1.dfs1(1, 0);
	t1.dfs2(1, 1);
	t2.dfs1(1, 0);
	t2.dfs2(1, 1);
	
	int k = 0;
	int l, r, tl, tr;
	
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &l, &r);
		tl = l = (l+k)%(n)+1;
		tr = r = (r+k)%(n)+1;
		while (l!=r) {
			if (l > r) {
				t1.jump(l, r);
			} else {
				t2.jump(r, l);
			}
		}
		k = l;
		
		printf("%d %d %d\n", l, t1.dep[tl] - t1.dep[l]+1, t2.dep[tr] - t2.dep[r]+1);
	}
}

int main(int argc, const char * argv[]) {
	while (scanf("%d %d", &n, &q) != EOF) {
		work();
	}
}
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
using namespace std;

#define N 100005

int n, q;

vector<int> g1[N];
vector<int> g2[N];

int mem = 0;
int siz[N], dep1[N], fa[N], hson[N], dep2[N];
int top1[N], w1[N], ww1[N], w2[N], ww2[N], top2[N];
int qz[N];

#define g g1
#define w w1
#define ww ww1
#define top top1
#define dep dep1
int dfs11(int n, int f) {
	dep[n] = dep[f]+1;
	fa[n] = f;
	int tot = 0;
	int tmp, p = 0, k = 0;
	if (g[n].size() > 0) {
		for (int i = 0; i < g[n].size(); i++) {
			tmp = dfs11(g[n][i], n);
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

void dfs12(int n, int fa) {
	w[n] = ++mem;
	ww[mem] = n;
	
	top[n] = fa;
	if (g[n].size() > 0) {
		dfs12(hson[n], fa);
		for (int i = 0; i < g[n].size(); i++) {
			if (g[n][i] != hson[n]) {
				dfs12(g[n][i], g[n][i]);
			}
		}
	}
}
#undef g
#undef w
#undef ww
#undef top
#undef dep

#define g g2
#define w w2
#define ww ww2
#define top top2
#define dep dep2
int dfs21(int n, int f) {
	dep[n] = dep[f]+1;
	fa[n] = f;
	int tot = 0;
	int tmp, p = 0, k = 0;
	if (g[n].size() > 0) {
		for (int i = 0; i < g[n].size(); i++) {
			tmp = dfs21(g[n][i], n);
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

void dfs22(int n, int fa) {
	w[n] = ++mem;
	ww[mem] = n;
	
	top[n] = fa;
	if (g[n].size() > 0) {
		dfs22(hson[n], fa);
		for (int i = 0; i < g[n].size(); i++) {
			if (g[n][i] != hson[n]) {
				dfs22(g[n][i], g[n][i]);
			}
		}
	}
}
#undef g
#undef w
#undef ww
#undef top
#undef dep

int jump1(int now, int tar) {
	int d = dep1[now];
	while (top1[now] >= tar) {
		now = top1[now];
	}
}

void work() {
	int tmp;
	for (int i = 0; i <= n; i++) {
		g1[i].clear();
		g2[i].clear();
	}
	
	for (int i = 2; i <= n; i++) {
		scanf("%d", &tmp);
		g1[tmp].push_back(i);
	}
	for (int i = 2; i <= n; i++) {
		scanf("%d", &tmp);
		g2[tmp].push_back(i);
	}

	dfs11(1, 0);
	dfs12(1, 1);
	dfs21(1, 0);
	dfs22(1, 1);
	
	int k = 0;
	int l, r;
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &l, &r);
		l = (l+k)%(n)+1;
		r = (r+k)%(n)+1;
		int lc = 0, rc = 0;
		
		while (l!=r) {
			if (l > r) {
				
				lc += jump1(l, r);
				
				//l = f1[l];
				//lc++;
			} else {
				
				rc += jump2(r, l);
				
				//r = f2[r];
				//rc++;
			}
		}
		k = l;
		
		printf("%d %d %d\n", l, lc+1, rc+1);
	}
}

int main(int argc, const char * argv[]) {
	while (scanf("%d %d", &n, &q) != EOF) {
		work();
	}
}

//
//  main.cpp
//  a2
//
//  Created by eycia on 13/9/15.
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

int va[10005];

vector<int > g[10005];
long long ii[10005];
bool v[10005];

priority_queue<int> pp;

int fa[10005];

int getf(int v) {
	return fa[v] < 0 ? v : fa[v] = getf(fa[v]);
}

void uni(int u, int v) {
	int f1 = getf(u), f2 = getf(v);
	if (f1 != f2) {
		fa[f1] += fa[f2];
		fa[f2] = f1;
	}
}

void work() {
	int p, m, l, r;
	scanf("%d %d", &p, &m);
	while (!pp.empty()) {
		pp.pop();
	}
	for (int i = 0; i < 10005; i++) {
		g[i].clear();
	}
	memset(v, false, sizeof(v));
	memset(ii, 0, sizeof(ii));
	memset(fa, -1, sizeof(fa));
	for (int i = 1; i <= p; i++) {
		scanf("%d", &va[i]);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &l, &r);
		g[l].push_back(r);
		g[r].push_back(l);
		ii[l]++;
		ii[r]++;
	}
	
	for (int i = 1; i <= p; i++) {
		if (ii[i] == 1 || ii[i] == 0) {
			pp.push(i);
			v[i] = true;
		}
	}
	
	while (!pp.empty()) {
		int k = pp.top();
		pp.pop();
		
		for (vector<int >::iterator it = g[k].begin(); it != g[k].end(); it++) {
			ii[*it]--;
			if (ii[*it] < 2 && !v[*it]) {
				v[*it] = true;
				pp.push(*it);
			}
		}
	}
	
	
	for (int i = 1; i <= p; i++) {
		for (vector<int >::iterator it = g[i].begin(); it != g[i].end(); it++) {
			if (!v[i] && !v[*it]) {
				uni(i, *it);
			}
		}
	}
	
	long long tot = 0;
	
	for (int i = 1; i <= p; i++) {
		if (!v[i]) {
			if ((-fa[getf(i)]) % 2 == 1) {
				tot += va[i];
			}
		}
	}
	
	cout << tot << endl;
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	while (t--) {
		work();
	}
}



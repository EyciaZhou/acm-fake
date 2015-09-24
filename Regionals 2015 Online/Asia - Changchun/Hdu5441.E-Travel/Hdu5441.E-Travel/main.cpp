//
//  main.cpp
//  a5
//
//  Created by eycia on 14/9/15.
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

vector<tuple<int, int, int > > g;
vector<pair<int, int> > qu;
long long ans[20005];
long long fa[20005];
long long a;

long long getf(long long a) {
	return fa[a] < 0 ? a : fa[a] = getf(fa[a]);
}

void inline uniq(int l, int r) {
	long long f1 = getf(l), f2 = getf(r);
	if (f1 != f2) {
		if (fa[f1] <= -2) {
			a -= fa[f1] * (fa[f1] + 1);
		}
		if (fa[f2] <= -2) {
			a -= fa[f2] * (fa[f2] + 1);
		}
		fa[f1] += fa[f2];
		a += fa[f1] * (fa[f1] + 1);
		fa[f2] = f1;
	}
}

void work() {
	qu.clear();
	g.clear();
	memset(fa, -1, sizeof(fa));
	a = 0;
	int n, m, q, l, r, v;
	scanf("%d %d %d", &n, &m, &q);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &l, &r, &v);
		g.push_back(make_tuple(v, l, r));
	}
	
	for (int i = 0; i < q; i++) {
		scanf("%d", &v);
		qu.push_back(make_pair(v, i));
	}
	sort(g.begin(), g.end());
	sort(qu.begin(), qu.end());
	
	int p = 0;
	for (int i = 0; i < q; i++) {
		while (p < m && get<0>(g[p]) <= qu[i].first) {
			uniq(get<1>(g[p]), get<2>(g[p]));
			p++;
		}
		ans[qu[i].second] = a;
	}
	
	for (int i = 0; i < q; i++) {
		printf("%lld\n", ans[i]);
	}
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		work();
	}
}

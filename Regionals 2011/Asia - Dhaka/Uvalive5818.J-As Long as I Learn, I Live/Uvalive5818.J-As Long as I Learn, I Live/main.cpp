//
//  main.cpp
//  Uvalive5818.J-As Long as I Learn, I Live
//
//  Created by eycia on 28/9/15.
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


vector<int> g[105];
int val[105];


void work(int ff) {
	int n, m, u, v;
	for (int i = 0; i < 105; i++) {
		g[i].clear();
	}
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &val[i]);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
	}
	
	int now = 0;
	int tot = 0;
	while (g[now].size() > 0) {
		int mx = 0;
		int p = 0;
		for (int i = 0; i < g[now].size(); i++) {
			if (val[g[now][i]] > mx) {
				mx = val[g[now][i]];
				p = g[now][i];
			}
		}
		tot += mx;
		now = p;
	}
	printf("Case %d: %d %d\n", ff, tot, now);
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int ff = 1; ff <= t; ff++) {
		work(ff);
	}
}

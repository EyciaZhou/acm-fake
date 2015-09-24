//
//  main.cpp
//  a4
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

int ans[150005];
char name[150005][300];

char tmp[205];

pair<int, int> sta[150005];

pair<int, int> door[150005];

priority_queue<pair<int, int>, vector<pair<int, int> >, less<pair<int, int> > > p;

void work() {
	while (!p.empty()) p.pop();
	int k, m, q, v, w, qq;
	scanf("%d %d %d", &k, &m, &q);
	for (int i = k-1; i >= 0; i--) {
		scanf("%s %d", name[i], &v);
		sta[i] = make_pair(v, i);
	}
	
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &v, &w);
		door[i] = make_pair(v, w);
	}
	sort(door, door+m);
	door[m] = make_pair(k, k);
	int now = 0, tot = 0;
	for (int i = 0; i <= m; i++) {
		for (int j = now; j < door[i].first; j++) {
			p.push(sta[k-j-1]);
		}
		now = door[i].first;
		for (int j = 0; j < door[i].second && !p.empty(); j++) {
			pair<int, int> k = p.top();
			p.pop();
			ans[tot++] = k.second;
		}
	}
	for (int i = 0; i < q; i++) {
		scanf("%d", &qq);
		if (i != 0) putchar(' ');
		printf("%s", name[ans[qq-1]]);
	}
	puts("");
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		work();
	}
}

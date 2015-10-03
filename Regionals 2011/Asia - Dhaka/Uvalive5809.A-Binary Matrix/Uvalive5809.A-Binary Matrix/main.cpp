//
//  main.cpp
//  Uvalive5809.A-Binary Matrix
//
//  Created by eycia on 30/9/15.
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


char tmp[1005];

int mp[1005][1005];
int h[1005], l[1005];

vector<int> t;

int abs(int a) {
	if (a < 0) {
		return -a;
	}
	return a;
}

int ga(int *p, int n) {
	t.clear();
	
	int tmp = 0;
	int tot = 0;
	for (int i = 0; i < n; i++) {
		tot += p[i];
	}
	int r = tot % n, w = tot / n;
	if (r != 0) return -1;
	
	for (int i = 0; i < n; i++) {
		t.push_back(tmp);
		tmp += p[i]-w;
	}
	sort(t.begin(), t.end());
	
	tot = 0;
	for (int i = 0; i < t.size(); i++) {
		tot += abs(t[n/2]-t[i]);
	}
	return tot;
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int ff = 1; ff <= t; ff++) {
		printf("Case %d: ", ff);
		memset(mp, 0, sizeof(mp));
		memset(h, 0, sizeof(h));
		memset(l, 0, sizeof(l));
		
		int n, m;
		scanf("%d %d", &n, &m);
		
		for (int i = 0; i < n; i++) {
			scanf("%s", tmp);
			for (int j = 0; j < m; j++) {
				mp[i][j] = tmp[j] - '0';
			}
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				h[i] += mp[i][j];
				l[j] += mp[i][j];
			}
		}
		
		int hh = ga(h, n), ll = ga(l, m);
		
		if (hh < 0 && ll >= 0) {
			printf("column %d\n", ll);
		}
		
		if (hh < 0 && ll < 0) {
			printf("impossible\n");
		}
		
		if (hh >= 0 && ll >= 0) {
			printf("both %d\n", ll+hh);
		}
		
		if (hh >= 0 && ll < 0) {
			printf("row %d\n", hh);
		}
	}
}

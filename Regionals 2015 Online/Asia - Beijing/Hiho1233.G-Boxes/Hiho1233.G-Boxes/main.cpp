//
//  main.cpp
//  Hiho1233.G-Boxes
//
//  Created by eycia on 22/9/15.
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

int qi[900000][7];
int to[900000];
int st[900000];
bool v[900000];
int ans[8][900000];

queue<int> q;



void gen(int n) {
	int mem;
	int c[7];
	int t[10];
	bool vv[10];
	
	t[0] = 1;
	int tot = 0;
	for (int i = 0; i < n; i++) {
		tot = tot * n + i;
	}
	
	for (int i = 0; i < n; i++) {
		qi[0][i] = i;
	}
	
	for (int i = 1; i < n; i++) {
		t[i] = t[i-1] * n;
	}

	to[0] = tot;
	st[0] = 0;
	v[tot] = true;
	mem = 0;
	q.push(0);
	
	int cnt = 0;
	while (!q.empty()) {
		cnt++;
		int k = q.front();
		q.pop();
	
		tot = to[k];
		
		for (int i = 0; i < n; i++) {
			c[i] = 0x7fffffff;
			vv[i] = false;
		}
		
		for (int i = 0; i < n; i++) {
			c[qi[k][i]] = min(c[qi[k][i]], i);
		}
		
		for (int i = 0; i < n; i++) {
			if (c[i] != 0x7fffffff) {
				vv[c[i]] = true;
			}
		}
		
		int a = 0;
		
		for (int i = 0; i < n; i++) {
			if (!vv[i]) continue;
			a++;
			if (qi[k][i]!=0 && c[qi[k][i]-1] > i) {
				if (!v[tot-t[n-i-1]]) {
					mem++;
					for (int i = 0; i < n; i++) {
						qi[mem][i] = qi[k][i];
					}
					qi[mem][i]--;
					q.push(mem);
					v[tot-t[n-i-1]] = true;
					to[mem] = tot-t[n-i-1];
					st[mem] = st[k]+1;
				}
			}
			
			if (qi[k][i]!=n-1 && c[qi[k][i]+1] > i) {
				if (!v[tot+t[n-i-1]]) {
					mem++;
					for (int i = 0; i < n; i++) {
						qi[mem][i] = qi[k][i];
					}
					qi[mem][i]++;
					q.push(mem);
					v[tot+t[n-i-1]] = true;
					to[mem] = tot+t[n-i-1];
					st[mem] = st[k]+1;
				}
			}
		}
		
		if (a == n) {
			ans[n][tot] = st[k];
		}
	}
}

void init() {
	memset(ans, -1, sizeof(ans));
	for (int i = 0; i <= 7; i++) {
		memset(v, false, sizeof(v));
		gen(i);
	}
}

vector<pair<int, int> > v1, v2;

void work() {
	v1.clear();
	v2.clear();
	
	int n, t;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		v1.push_back(make_pair(t, i));
	}
	sort(v1.begin(), v1.end());
	
	int tot = 0;
	
	for (int i = 0; i < n; i++) {
		tot = tot * n + v1[i].second;
	}
	cout << ans[n][tot] << endl;
}

int main(int argc, const char * argv[]) {
	int t;
	
	init();
	
	scanf("%d", &t);
	while (t--) {
		work();
	}
}
//
//  main.cpp
//  Uvalive5713.A-Qin Shi Huang's National Road System
//
//  Created by eycia on 24/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
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

vector<pair<int, int> > ps;
vector<int> vs;
double mp[1005][1005];
int va[1005][1005];
double pa[1005][1005];
bool mm[1005][1005];

inline double dist(int i, int j) {
	return sqrt((ps[i].first - ps[j].first) * (ps[i].first - ps[j].first) +
				(ps[i].second - ps[j].second) * (ps[i].second - ps[j].second));
}

#define typec double
const typec inf = 0x3f3f3f3f;
int vis[1005];
typec lowc[1005];

#define cost mp
typec prim(int n) {
	int i, j, p;
	typec minc, res = 0;
	memset(vis, 0, sizeof(vis));
	memset(pa, 0, sizeof(pa));
	memset(mm, false, sizeof(mm));
	vis[0] = 1;
	for (int i = 1; i < n; i++) lowc[i] = cost[0][i];
	for (int i = 1; i < n; i++) {
		minc = inf; p = -1;
		for (j = 0; j < n; j++) {
			if (vis[j] == 0 && minc > lowc[j]) {
				minc = lowc[j];
				p = j;
			}
		}
		if (inf == minc) return -1;
		
		int ii = 0;
		for (int i = 0; i < n; i++) {
			if (vis[i]) {
				if (mp[i][p] == minc) {
					ii = i;
				}
			}
		}
		//cout << ii << " aa " << p << " " << minc << endl;
		mm[ii][p] = mm[p][ii] = true;
		for (int i = 0; i < n; i++) {
			if (vis[i]) {
				pa[p][i] = max(pa[ii][i], minc);
				pa[i][p] = max(pa[ii][i], minc);
			}
		}
		
		res += minc; vis[p] = 1;
		for (j = 0; j < n; j++) {
			if (vis[j] == 0 && lowc[j] > cost[p][j]) {
				lowc[j] = cost[p][j];
			}
		}
	}
	return res;
}
#undef cost

int main(int argc, const char * argv[]) {
	int t, x, y, v;
	scanf("%d", &t);
	while (t--) {
		int n;
		
		ps.clear();
		vs.clear();
		
		scanf("%d", &n);
	
		for (int i = 0; i < n; i++) {
			scanf("%d %d %d", &x, &y, &v);
			ps.push_back(make_pair(x, y));
			vs.push_back(v);
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) continue;
				mp[i][j] = mp[j][i] = dist(i, j);
				va[i][j] = vs[i];
				va[j][i] = vs[j];
			}
		}
		
		double mst = prim(n);
		double mx = 0;
		/*
		cout << mst << endl;
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d ", mm[i][j]);
			}
			printf("\n");
		}
		
		puts("");
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%lf ", pa[i][j]);
			}
			printf("\n");
		}
		*/
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) continue;
				
				if (mm[i][j]) {
					mx = max(mx, (va[i][j] + va[j][i]) / (mst-mp[i][j]));
				} else {
					mx = max(mx, (va[i][j] + va[j][i]) / (mst-pa[i][j]));
				}
			}
		}
		
		printf("%.2lf\n", mx);
	}
}

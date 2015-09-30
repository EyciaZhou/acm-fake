//
//  main.cpp
//  Uvalive5811.C-Cards
//
//  Created by eycia on 29/9/15.
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

double f[15][15][15][15][3][3][3][3];
int v[15][15][15][15][3][3][3][3];

int cds[4];

#define eps 1e-9

int cas;

double dfs(int a, int b, int c, int d, int ra, int rb, int rc, int rd) {
	if (v[a][b][c][d][ra][rb][rc][rd] == cas) {
		return f[a][b][c][d][ra][rb][rc][rd];
	}
	if (a+ra >= cds[0] && b+rb >= cds[1] && c+rc >= cds[2] && d+rd >= cds[3]) {
		return a+b+c+d+ra+rb+rc+rd;
	}
	double tot = 0;
	int cs = 54-a-b-c-d-ra-rb-rc-rd;
	if (a < 13) tot += dfs(a+1, b, c, d, ra, rb, rc, rd) * (13-a) / cs;
	if (b < 13) tot += dfs(a, b+1, c, d, ra, rb, rc, rd) * (13-b) / cs;
	if (c < 13) tot += dfs(a, b, c+1, d, ra, rb, rc, rd) * (13-c) / cs;
	if (d < 13) tot += dfs(a, b, c, d+1, ra, rb, rc, rd) * (13-d) / cs;

	int wei = 2 - ra - rb- rc - rd;
	if (wei > 0) {
		vector<double> ds;
		ds.push_back(dfs(a, b, c, d, ra+1, rb, rc, rd) * (wei) / cs);
		ds.push_back(dfs(a, b, c, d, ra, rb+1, rc, rd) * (wei) / cs);
		ds.push_back(dfs(a, b, c, d, ra, rb, rc+1, rd) * (wei) / cs);
		ds.push_back(dfs(a, b, c, d, ra, rb, rc, rd+1) * (wei) / cs);
		sort(ds.begin(), ds.end());
		int k = 0;
		while (ds[k] < eps && k < 3) k++;
		if (!(ds[k] < eps)) {
			tot += ds[k];
		}
	}
	f[a][b][c][d][ra][rb][rc][rd] = tot;
	v[a][b][c][d][ra][rb][rc][rd] = cas;
	return tot;
}

void work() {
	//memset(v, false, sizeof(v));
	for (int i = 0; i < 4; i++) {
		scanf("%d", &cds[i]);
	}
	sort(cds, cds+4);
	
	if (cds[3] > 15 || cds[1] > 13 || cds[2]+cds[3] > 28) {
		printf("%.3lf\n", -1.0);
	} else {
		printf("%.3lf\n", dfs(0, 0, 0, 0, 0, 0, 0, 0));
	}
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		cas = i;
		printf("Case %d: ", i);
		work();
	}
}

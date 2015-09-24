//
//  main.cpp
//  csp 201412-2
//
//  Created by eycia on 4/9/15.
//  Copyright (c) 2015 eycia. All rights reserved.
//

#include <set>
#include <map>
#include <list>
//#include <tuple>
//#include <ratio>
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

int n;
int mat[505][505];

inline bool out_bound(int tx, int ty) {
	return tx < 0 || ty < 0 || tx >= n || ty >= n;
}

void dfs(int x, int y, int up) {
	int tx = x-up, ty = y+up;
	if (!out_bound(x, y)) {
		printf("%d ", mat[x][y]);
	}
	if (x == n && y == n) return;
	if (out_bound(tx, ty)) {
		if (up >= 0) {
			dfs(x, y+1, -up);
		} else {
			dfs(x+1, y, -up);
		}
	} else {
		dfs(tx, ty, up);
	}
}

int main(int argc, const char * argv[]) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
	
	dfs(0, 0, 1);
}

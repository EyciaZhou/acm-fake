//
//  main.cpp
//  Uvalive5790.B-Ball Stacking
//
//  Created by eycia on 22/8/15.
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

long long mp[1005][1005];
long long g[1005][1005];
long long f[1005][1005];

int main(int argc, const char * argv[]) {
	int n;
	while (scanf("%d", &n) != EOF) {
		if (n == 0) break;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				scanf("%lld", &mp[i-j+1][j]);
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n-i+1; j++) {
				g[i][j] = g[i][j-1] + mp[i][j];
			}
		}
		
		long long mx = 0;
		
		for (int i = 0; i <= n+4; i++) {
			for (int j = 0; j <= n+4; j++) {
				f[i][j] = -0x7fffffffffffffff;
			}
		}
		
		for (int j = n; j >= 1; j--) {
			f[1][j] = max(f[1][j+1], g[1][j]);
			mx = max(mx, f[1][j]);
		}
		
		for (int i = 2; i <= n; i++) {
			f[i][n-i+1] = f[i-1][n-i+1] + g[i][n-i+1];
			mx = max(mx, f[i][n-i+1]);
			for (int j = n-i; j >= 1; j--) {
				f[i][j] = max(f[i][j+1], f[i-1][j] + g[i][j]);
				mx = max(mx, f[i][j]);
			}
		}
		
		cout << mx << endl;
	}
}
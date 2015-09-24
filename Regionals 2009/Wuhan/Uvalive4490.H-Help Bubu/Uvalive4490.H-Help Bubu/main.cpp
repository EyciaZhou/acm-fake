//
//  main.cpp
//  Uvalive4490.H-Help Bubu
//
//  Created by eycia on 21/8/15.
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

int a[105];

int f[105][105][300][10];

int main(int argc, const char * argv[]) {
	int n, k;
	int ff = 0;
	while (scanf("%d %d", &n, &k), n+k) {
		ff++;
		int mm = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			a[i] -= 25;
			mm |= (1 << a[i]);
		}
		memset(f, -1, sizeof(f));
		f[1][0][1 << a[1]][a[1]] = 1;
		f[1][1][0][9] = 0;
		for (int i = 2; i <= n; i++) {
			for (int mask = 0; mask < 256; mask++) {
				for (int j = 0; j <= k; j++) {
				for (int l = 0; l <= 9; l++) {
					if (!(mask & (1 << a[i]))) {
						if (f[i-1][j][mask][l] >= 0 && (f[i-1][j][mask][l] + 1 < f[i][j][mask | (1 << a[i])][a[i]] || f[i][j][mask | (1 << a[i])][a[i]] < 0)) {
							f[i][j][mask | (1 << a[i])][a[i]] = f[i-1][j][mask][l]+1;
						}
						if (j >= 1 && f[i-1][j-1][mask][l] >= 0 && (f[i][j][mask][l] < 0 || f[i][j][mask][l] > f[i-1][j-1][mask][l])) {
							f[i][j][mask][l] = f[i-1][j-1][mask][l];
						}
					} else {
						if (j >= 1 && f[i-1][j-1][mask][l] >= 0 && (f[i][j][mask][l] < 0 || f[i][j][mask][l] > f[i-1][j-1][mask][l])) {
							f[i][j][mask][l] = f[i-1][j-1][mask][l];
						}
						if (f[i-1][j][mask][l] >= 0) {
							if (a[i] != l) {
								if (f[i-1][j][mask][l] + 1 < f[i][j][mask][a[i]] || f[i][j][mask][a[i]] < 0) {
									f[i][j][mask][a[i]] = f[i-1][j][mask][l] + 1;
								}
							} else {
								if (f[i-1][j][mask][l] < f[i][j][mask][a[i]] || f[i][j][mask][a[i]] < 0) {
									f[i][j][mask][a[i]] = f[i-1][j][mask][l];
								}
							}
						}
					}
				}
				}
			}
		}
		int mi = 0x7fffffff;
		for (int j = 0; j <= k; j++) {
			for (int mask = 0; mask < 256; mask++) {
				int ex = bitset<8>(mm).count() - bitset<8>(mask).count();
				if (ex < 0) continue;
				for (int i = 0; i <= 9; i++) {
					if (f[n][j][mask][i] >= 0 && f[n][j][mask][i] + ex < mi) {
						mi = f[n][j][mask][i] + ex;
					}
				}
			}
		}
		printf("Case %d: %d\n\n", ff, mi);
	}
}
/*
 5 1
 25 26 25 25 25
 
 10 2
 25 27 26 25 25 26 26 26 26 26
 
 9 0
 25 26 27 28 29 28 27 26 25
 
 9 1
 25 26 27 28 29 28 27 26 25
 
 9 2
 25 26 27 28 29 28 27 26 25
 
 9 3
 25 26 27 28 29 28 27 26 25
 
 9 4
 25 26 27 28 29 28 27 26 25
 
 9 5
 25 26 27 28 29 28 27 26 25
 
 10 1
 26 27 27 27 27 27 27 26 28 27
 
 10 2
 26 27 27 27 27 27 27 26 28 27
 
 16 7
 30 32 30 30 32 29 28 29 25 30 29 29 29 27 30 26
 
 16 7
 30  30 30 30 32 32 29  29 29 29 29 28 25 27 30 26
 
 33 15
 32 28 25 28 29 30 28 28 32 32 30 30 32 31 31 26 28 30 26 26 30 32 25 29 29 30 30 28 30 29 29 25 30
 
 13 4
 30 28 31 27 31 32 30 32 28 26 32 32 27
 
 0 0
 
 13 4
 30 28 31 27 31 32 30 32 28 26 32 32 27
 
 13 3
 30 28 28 31 27 31 32 30 32 26 32 32 27
 
 13 2
 30 28 28 26 31 27 31 32 30 32 32 32 27
 
 13 1
 30 28 28 26 31 31 32 30 32 32 32 27 27
 
 13 0
 30 30 28 28 26 31 31 32 32 32 32 27 27
 
 5 1
 25 26 25 25 25
 
 0 0
*/
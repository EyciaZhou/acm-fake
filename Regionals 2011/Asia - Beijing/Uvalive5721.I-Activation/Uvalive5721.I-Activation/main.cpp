//
//  main.cpp
//  Uvalive5721.I-Activation
//
//  Created by eycia on 5/9/15.
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

double f[2005][2005][2];

double p[2005];

int main(int argc, const char * argv[]) {
	int n, m, k;
	double p1, p2, p3, p4;
	while (scanf("%d %d %d %lf %lf %lf %lf", &n, &m, &k, &p1, &p2, &p3, &p4) != EOF) {
		if (p1 + p2 == 1) {
			printf("%.5lf\n", 0.0);
			continue;
		}
		p2 /= 1-p1;
		p3 /= 1-p1;
		p4 /= 1-p1;
		
		p[0] = 1;
		for (int i = 1; i <= n; i++) {
			p[i] = p[i-1]*p2;
		}
		
		memset(f[n+1], 0, sizeof(f[n+1]));
		f[n+1][m+1][0] = 1;
	
		double tmp = 0;
		for (int j = 1; j < n; j++) {
			tmp += f[n+1][j+1][0]*p[j];
		}
		tmp += f[n+1][n+1][0];
		tmp /= (1 - p[n]);
		
		f[n][n][0] = tmp;
		f[n][n][1] = tmp * p4;
		
		for (int j = n-1; j >= 1; j--) {
			f[n][j][0] = f[n][j+1][0]*p2+f[n+1][j+1][0];
			f[n][j][1] = f[n][j][0] * p4;
		}

	
		for (int i = n-1; i > 0; i--) {
			double tmp = 0;
			for (int j = 1; j < i; j++) {
				tmp += f[i+1][j+1][0]*p[j]*p3;
			}
			tmp += f[i+1][i+1][0]*p3;
			tmp /= (1 - p[i]);
			f[i][i][0] = tmp;
			f[i][i][1] = tmp * p4;
		
			for (int j = i-1; j >= 1; j--) {
				f[i][j][0] = f[i][j+1][0]*p2+f[i+1][j+1][0]*p3;
				f[i][j][1] = f[i][j][0]*p4;
			}
		}
		double tot = 0;
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= k; j++) {
				tot += f[i][j][1];
			}
		}
		printf("%.5lf\n", tot);
	}
}

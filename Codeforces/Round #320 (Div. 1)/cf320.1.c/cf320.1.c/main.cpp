//
//  main.cpp
//  cf320.1.c
//
//  Created by eycia on 17/9/15.
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

double a[200005];
double b[200005];
double c[200005];
int n;


double val(double k) {
	bool f1 = false, f2 = false;
	double mmx = -1, mmi=1e12;
	
	b[0] = c[0] = a[0]-k;
	for (int i = 1; i < n; i++) {
		b[i] = a[i]-k;
		if (b[i-1] > 0) {
			b[i] += b[i-1];
		}
	}
	
	for (int i = 1; i < n; i++) {
		c[i] = a[i]-k;
		if (c[i-1] < 0) {
			c[i] += c[i-1];
		}
	}
	
	for (int i = 0; i < n; i++) {
		if (b[i] > mmx) {
			f1 = true;
			mmx = b[i];
		}
		if (c[i] < mmi) {
			f2 = true;
			mmi = c[i];
		}
	}
	
	if (!f1) return -mmi;
	if (!f2) return mmx;
	
	return max(mmx, -mmi);
}

int main(int argc, const char * argv[]) {
	scanf("%d", &n);
	
	double ma = -1;
	
	for (int i = 0; i < n; i++) {
		scanf("%lf", &a[i]);
		ma = max(ma, fabs(a[i]));
	}
	
	double l = -ma, r = ma, m, mm;
	for (int t = 0; t < 100; t++) {
		m = (l + r) / 2;
		mm = (m + r) / 2;
		if (val(m) < val(mm)) {
			r = mm;
		} else {
			l = m;
		}
	}
	printf("%.10lf\n", val(l));
	
}

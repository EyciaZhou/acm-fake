//
//  main.cpp
//  1001.A-Pyramid Split
//
//  Created by eycia on 12/9/15.
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

int a[10005], b[10005];


double getto(double hi) {
	double tot = 0;
	for (int i = 0; i < n; i++) {
		if (hi < a[i]) {
			double rest = a[i] - hi;
			double radio = rest / a[i];
			tot += b[i]*b[i]*rest/3.0*radio*radio;
		}
	}
	return tot;
}

void work() {
	
	double tot = 0;
	
	int hi = 0;
	
	for (int i = 0; i < n; i++) {
		tot += b[i]*b[i]*a[i]/3.0;
		hi = max(hi, a[i]);
	}

	double le = 0, ri = hi;
	
	for (int i = 0; i < 100; i++) {
		double mi = (le + ri) / 2;
		
		if (getto(mi) < tot*0.5) {
			ri = mi;
		} else {
			le = mi;
		}
	}
	
	printf("%d\n", (int)(le));
}


int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		for (int i = 0; i < n; i++) {
			scanf("%d", &b[i]);
		}
		
		work();
		
	}
}

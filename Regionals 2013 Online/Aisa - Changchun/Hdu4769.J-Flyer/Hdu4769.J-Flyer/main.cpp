//
//  main.cpp
//  Hdu4769.J-Flyer
//
//  Created by eycia on 9/9/15.
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

int n;
long long a[20005], b[20005], c[20005];

long long in_left(long long le, long long mi) { //include mi
	long long tot = 0;
	for (int i = 0; i < n; i++) {
		if (c[i] == 0) {
			continue;
		}
		if (b[i] >= le && a[i] <= mi) {
			long long ll, rl;
			rl = min(mi, b[i]);
			if (le <= a[i]) {
				ll = a[i];
			} else {
				long long k = le - a[i];
				long long k2 = ceil((k+0.0) / c[i]);
				ll = a[i] + k2 * c[i];
			}
			if (ll > rl) {
				continue;
			}
			tot += (rl - ll) / c[i] + 1;
			//printf("In Seg %d : [%lld, %lld], have %lld\n", i, le, mi, (rl - ll) / c[i] + 1);
		}
	}
	//printf("[%lld, %lld] : %lld\n\n", le, mi, tot);
	return tot;
}

int main(int argc, const char * argv[]) {
	while (scanf("%d", &n) != EOF) {
		for (int i = 0 ; i < n; i++) {
			scanf("%d %d %d", &a[i], &b[i], &c[i]);
		}
		
		long long le = 1, ri = 0xffffffff;
		//cout << ri << endl;
		
		if (in_left(le, ri) % 2 == 0) {
			puts("DC Qiang is unhappy.");
			continue;
		}
		
		while (le != ri) {
			long long mi = (le + ri) / 2;
			//cout << le << " " << mi << " " << ri << endl;
			if (in_left(le, mi) % 2 == 1) {
				ri = mi;
			} else {
				le = mi+1;
			}
		}
		cout << le << " " << in_left(le, le) << endl;
	}
}

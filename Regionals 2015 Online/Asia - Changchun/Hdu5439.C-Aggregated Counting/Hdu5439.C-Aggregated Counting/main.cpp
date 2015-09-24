//
//  main.cpp
//  Hdu5439.C-Aggregated Counting
//
//  Created by eycia on 16/9/15.
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

vector<int> vec;
/*
 0 1 3 5 8 11 15 19 23 28 33 38 44 50 56 62 69 76 83 90 98 106 114 122 131 140 149 158 167 177 187 197 207 217 228 239 250 261 272 284 296 308 320 332 344 357 370 383 396 409 422 436 450 464 478 492
 */

/*
 0 1 5 11 23 38 62 90 122 167 217 272 344 422 506 596 708 827 953 1086 1246 1414 1590 1774 1990 2215 2449 2692 2944 3234 3534 3844 4164 4494 4868 5253 5649 6056 6474 6942 7422 7914 8418 8934 9462 10047 10645 11256 11880 12517 13167 13881 14609 15351 16107 16877 17661 18516 19386 20271 21171 22086 23016 24024 25048 26088 27144 28216 29304 30408 31598 32805 34029 35270 36528 37803 39095 40481 41885 43307 44747 46205 47681
 */

bool gr(double uu) {
	int i = 100;
	long long k = pow(i, uu);
	double rate1 = (double)(k) / vec[vec[i]];
	
	i = 2000;
	k = pow(i, uu);
	double rate2 = (double)(k) / vec[vec[i]];
	
	return rate1 > rate2;
}

int main(int argc, const char * argv[]) {
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(2);
	for (int i = 3; i < 100000; i++) {
		for (int j = 0; j < vec[i]; j++) {
			vec.push_back(i);
		}
	}
	for (int i = 1; i < vec.size(); i++) {
		vec[i] = (vec[i] + vec[i-1]) % 1000000007;
	}
	
	/*
	for (int i = 0; i < 1000; i++) {
		printf("%d ", lst[i]);
	}
	puts("");*/
	
	double le = 2, ri = 3;
	
	for (int i = 0; i < 100; i++) {
		double mi = (le + ri) / 2;
		
		if (!gr(mi)) {
			ri = mi;
		} else {
			le = mi;
		}
	}
	
	printf("%.10lf\n", le);
	
	for (int i = 0; i < vec.size(); i++) {
		long long k = pow(i, 2.6142615909);
		double rate = (double)(k) / vec[vec[i]];
		printf("%lld %d %lf %d\n ", k, i, rate, vec[vec[i]]);
	}
	puts("");
	cout << vec.size() << endl;
}

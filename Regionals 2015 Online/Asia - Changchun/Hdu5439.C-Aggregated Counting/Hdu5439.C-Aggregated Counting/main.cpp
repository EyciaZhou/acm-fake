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

#define ll long long

vector<ll> lst;
vector<ll> mu;
vector<ll> mut;
vector<ll> gst;

//74900845

void init() {
	lst.reserve(440000);
	mu.reserve(440000);
	mut.reserve(440000);
	gst.reserve(440000);
	
	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(2);
	
	mu.push_back(1);
	mu.push_back(4);
	mu.push_back(6);
	
	long long k = 4;
	for (int i = 2; i < 3689; i++) {
		for (int j = 0; j < lst[i]; j++) {
			lst.push_back(i+1);
			mu.push_back((i+1) * k);
			k++;
		}
	}
	
	mut.push_back(1);
	for (int i = 1; i < mu.size(); i++) {
		mut.push_back(mu[i]+mut[i-1]);
	}
	
	for (int i = 1; i < lst.size(); i++) lst[i] += lst[i-1];
	
	gst.push_back(1);
	for (int i = 1; i < lst.size(); i++) {
		gst.push_back((lst[i-1]+1+lst[i])*mu[i]/2);
	}
	
	for (int i = 1; i < 3700; i++) gst[i] += gst[i-1];
	
	for (int i = 3700; i < gst.size(); i++) gst[i] = (gst[i]+gst[i-1]) % 1000000007;
}

long long get(long long n) {
	long k = upper_bound(mut.begin(), mut.end(), n) - mut.begin() - 1;
	
	long long p = k+2;
	long long st = lst[k]+1;
	long long pos = mut[k];
	
	long long ds = (n - pos) / p;
	long long ss = st+ds-1;
	
	long long z = (st + ss) * (p * ds) / 2;
	
	long long z2 = (ss+1) * (n-pos-p*ds);
	
	return gst[k] + z + z2;
}

void work(long long n) {
	cout << get(get(n)) % 1000000007 << endl;
}

int main(int argc, const char * argv[]) {
	init();
	long long t, n;
	scanf("%lld", &t);
	for (int i = 0; i < t; i++) {
		scanf("%lld", &n);
		work(n);
	}
}

//
//  main.cpp
//  Uvalive7045.K-Last Defence
//
//  Created by eycia on 18/9/15.
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

vector<long long> seg;

long long aabs(long long a) {
	if (a < 0) {
		return -a;
	}
	return a;
}

long long gcd(long long x, long long y){
	long long tot = 0;
	
	if (x < y) swap(x, y);
	
	if (!x || !y) {
		if (x == 0 && y == 0) {
			return 1;
		} else {
			return 2;
		}
	}
	for (long long t; ; x = y, y = t) {
		t = x % y;
		tot += (x-y)/y+1;
		if (t==0) {
			break;
		}
	}
	return tot+1;
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	
	for (int ff = 1; ff <= t; ff++) {
		long long l, r;
		cin >> l >> r;
		cout <<"Case #" << ff <<": "<< gcd(l, r) << endl;
	}
}

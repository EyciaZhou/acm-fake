//
//  main.cpp
//  cf.320.1.b
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

long long a[200005];
long long suf[200005];
long long pre[200005];

int main(int argc, const char * argv[]) {
	long long n, k, x;
	cin >> n >> k >> x;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	
	long long mul = 1;
	for (int i = 0; i < k; i++) {
		mul *= x;
	}
	
	
	for (long long i = 1; i <= n; i++) {
		suf[i] = suf[i-1] | a[i];
	}
	
	for (long long i = n; i >= 1; i--) {
		pre[i] = pre[i+1] | a[i];
	}
	
	long long mx = 0;
	
	for (long long i = 1; i <= n; i++) {
		mx = max(mx, suf[i-1]|(a[i]*mul)|pre[i+1]);
	}
	
	cout << mx << endl;
}

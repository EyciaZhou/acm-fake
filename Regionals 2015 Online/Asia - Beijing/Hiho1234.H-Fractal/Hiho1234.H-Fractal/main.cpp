//
//  main.cpp
//  a2
//
//  Created by eycia on 20/9/15.
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
#include <ext/rope>
using namespace std;

#define eps 1e-9

void work() {
	double k;
	scanf("%lf", &k);
	
	double an = log(0.5-k)/log(0.5);
	
	long long a2 = an;
	
	if (fabs(an - a2) < eps) {
		puts("-1");
		return;
	}
	
	if (k == 0.5) {
		puts("1000");
		return ;
	}
	
	printf("%lld\n", a2 * 4);
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		work();
	}
}

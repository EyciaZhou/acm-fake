//
//  main.cpp
//  g3
//
//  Created by eycia on 19/9/15.
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

#define MOD 530600414

long long a[250000], l[250000], r[250000], ll[250000], num[250000];

int main(int argc, const char * argv[]) {
	a[3] = 0;
	a[4] = 0;
	
	l[3] = 0;
	l[4] = 2;
	
	r[3] = 2;
	r[4] = 2;
	
	ll[3] = 3;
	ll[4] = 5;
	
	num[3] = 1;
	num[4] = 1;
	
	for (int i = 5; i <= 201314; i++) {
		l[i] = (l[i-2] + ll[i-2] * num[i-1] % MOD + l[i-1]) % MOD;
		
		r[i] = (r[i-1] + ll[i-1] * num[i-2] % MOD + r[i-2]) % MOD;
		
		a[i] = (((num[i-2]*l[i-1] % MOD + num[i-1]*r[i-2] % MOD) % MOD + (num[i-1]*num[i-2] % MOD + a[i-1]) % MOD) % MOD + a[i-2]) % MOD;
		
		ll[i] = (ll[i-1] + ll[i-2]) % MOD;
		
		num[i] = (num[i-1] + num[i-2]) % MOD;
	}
	
	int t, n;
	scanf("%d", &t);
	
	for (int ff = 1; ff <= t; ff++) {
		scanf("%d", &n);
		cout << "Case #" << ff << ": ";
		cout << a[n] << endl;
	}
}
/*
 0
 0
 5
 5 5 3 5
 */
//
//  main.cpp
//  Uvalive7040.F-Color
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

#define MOD 1000000007

#define int long long
int ex(int base, int up, long long mod) {
	int res = 1;
	int tmp = base;
	while (up) {
		if (up & 1) {
			res = res * tmp % mod;
		}
		tmp = tmp * tmp % mod;
		up >>= 1;
	}
	return res;
}
#undef int

#define ll long long

ll comp(ll a, ll b, ll p) {
	if(a < b)   return 0;
	if(a == b)  return 1;
	if(b > a - b)   b = a - b;
	
	ll ans = 1, ca = 1, cb = 1;
	for(ll i = 0; i < b; ++i) {
		ca = (ca * (a - i))%p;
		cb = (cb * (b - i))%p;
	}
	ans = (ca*ex(cb, p - 2, p)) % p;
	return ans;
}

ll lucas(ll n, ll m, ll p) {
	ll ans = 1;
	while(n&&m&&ans) {
		ans = (ans*comp(n%p, m%p, p)) % p;
		n /= p;
		m /= p;
	}
	return ans;
}

long long ge(long long nu, long long cn) {
	return (cn * ex(cn-1, nu-1, MOD)) % MOD;
}

void work(int ff) {
	long long n, m, k;
	cin >> n >> m >> k;
	
	long long ans = ge(n, k);
	//cout << lucas(m, k, MOD) << endl;
	printf("Case #%d: %lld\n", ff, ans * lucas(m, k, MOD)%MOD);
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		work(i);
	}
}
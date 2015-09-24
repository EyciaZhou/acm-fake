//
//  main.cpp
//  Uvalive5798.J-Jupiter Atacks!
//
//  Created by eycia on 21/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
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

long long MOD;

struct BIT {
#define BIT_MAX_LEN 100005
	typedef long long BIT_TYPE;
	
	BIT_TYPE c[BIT_MAX_LEN];
	int len;
	
	inline int lowbit(int x) {
		return x & (-x);
	}
	
	inline void build(int l) {
		memset(c, 0, sizeof(c));
		len = l;
	}
	
	inline void modify(int index, BIT_TYPE delta) {
		for (int i = index; i <= len; i += lowbit(i)) {
			c[i] = (c[i] + delta + MOD) % MOD;
		}
	}
	
	inline BIT_TYPE sum(int k) {
		BIT_TYPE ans = 0;
		for (int i = k; i > 0; i -= lowbit(i)) {
			ans = (ans + c[i] + MOD) % MOD;
		}
		return ans;
	}
	
	inline BIT_TYPE sum(int s, int e) {
		if (s > e) {
			swap(s, e);
		}
		if (s == 0) {
			return sum(e) % MOD;
		}
		return (sum(e) - sum(s - 1) + MOD) % MOD;
	}
	
#undef BIT_MAX_LEN
};

long long v[100005];

BIT bit;

long long B, N;

#define int long long
int exp(int base, int up, long long mod) {
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

inline long long f(long long k, int index) {
	return (exp(B, N-index, MOD) * k) % MOD;
}

int main(int argc, const char * argv[]) {
	int b, p, l, n, lh, rh;
	char o[10];
	while (scanf("%d %d %d %d", &b, &p, &l, &n) != EOF) {
		if (b+p+l+n == 0) break;
		memset(v, 0, sizeof(v));
		MOD = p;
		B = b;
		N = l;
		bit.build(l);
		for (int i = 0; i < n; i++) {
			scanf("%s %d %d", o, &lh, &rh);
			if (o[0] == 'E') {
				bit.modify(lh, -f(v[lh], lh));
				bit.modify(lh, f(rh, lh));
				v[lh] = rh;
			} else {
				printf("%lld\n", bit.sum(lh, rh) * exp(exp(B, l-rh, MOD), MOD-2, MOD) % MOD);
			}
		}
		puts("-");
	}
}
/*
 20 1000000007 5 7
 E 1 12
 E 2 14
 E 3 2
 E 4 2
 E 5 4
 H 2 5
 E 2 14
*/
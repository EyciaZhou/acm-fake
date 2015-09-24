//
//  main.cpp
//  Hdu4762.D-Cut the Cake
//
//  Created by eycia on 10/9/15.
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

typedef vector<int> lnum;

void lnum_mul(lnum &l, long long r) {
	long long lst = 0;
	for (int i = 0; i < l.size(); i++) {
		lst += l[i] * r;
		l[i] = lst % 10;
		lst /= 10;
	}
	while (lst > 0) {
		l.push_back(lst % 10);
		lst /= 10;
	}
}

void lnum_pr(lnum &l) {
	if (l.size() == 0) {
		puts("0");
		return;
	}
	for (int i = l.size()-1; i >= 0; i--) {
		printf("%d", l[i]);
	}
	puts("");
}

void lnum_mul_exp(long long base, long long up, lnum &res) {
	if (up == 0) {
		return;
	}
	for (int i = 0; i < up; i++) {
		lnum_mul(res, base);
	}
}

#define int long long
int exp(int base, int up) {
	int res = 1;
	int tmp = base;
	while (up) {
		if (up & 1) {
			res = res * tmp;
		}
		tmp = tmp * tmp;
		up >>= 1;
	}
	return res;
}
#undef int

int main(int argc, const char * argv[]) {
	int t;
	long long ll, rr;
	scanf("%d", &t);
	lnum l;
	while (t--) {
		cin >> ll >> rr;
	
		long long lhs = rr, rhs = exp(ll, min(rr-1, (long long)6)), g = __gcd(lhs, rhs);
		lhs /= g; rhs /= g;
		if (rr-1 <= 6) {
			cout << lhs << "/" << rhs << endl;
		} else {
			rr -= 7;
			l.clear();
			while (rhs > 0) {
				l.push_back(rhs%10);
				rhs/=10;
			}
			lnum_mul_exp(ll, rr, l);
			cout << lhs << "/";
			lnum_pr(l);
		}
	}
}

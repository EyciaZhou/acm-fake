//
//  main.cpp
//  a3
//
//  Created by eycia on 13/9/15.
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
#include <limits>
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

long long lnum_mod(lnum &l, long long m) {
	
	long long t = 0, ten = 1;
	
	for (int i = 0; i < l.size(); i++) {
		t = (t + ten*l[i]%m) % m;
		ten = (ten*10) % m;
	}
	return t;
}

void lnum_from(lnum &l, long long r) {
	l.clear();
	if (r == 0) {
		l.push_back(0);
		return;
	}
	while (r > 0) {
		l.push_back(r%10);
		r/=10;
	}
}

#define ll long long
#define int long long

int quick_power_mod(int a,int b,int m){//pow(a,b)%m
	int result = 1;
	int base = a;
	while(b>0){
		if((b & 1)==1){
			result = (result*base) % m;
		}
		base = (base*base) %m;
		b>>=1;
	}
	return result;
}

ll comp(ll a, ll b, ll p) {
	if(a < b)   return 0;
	if(a == b)  return 1;
	if(b > a - b)   b = a - b;
	
	int ans = 1, ca = 1, cb = 1;
	for(ll i = 0; i < b; ++i) {
		ca = (ca * (a - i))%p;
		cb = (cb * (b - i))%p;
	}
	ans = (ca*quick_power_mod(cb, p - 2, p)) % p;
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

#define LL long long
int m[15];
int a[15];
int extgcd(int a, int b, int & x, int & y){
	if (b == 0) { x=1; y=0; return a; } int d = extgcd(b, a % b, x, y);
	int t = x; x = y; y = t - a / b * y; return d;
}
int china(int b[], int w[], int k){
	int i, d, x=0, y=0, m, a = 0, n = 1;
	lnum aa, bb, cc;
	for (i = 0; i < k; i++) n *= w[i];
	for (i = 0; i < k; i++) {
		m = n / w[i];
		d = extgcd(w[i], m, x, y);
		int t = y;
		while (t < 0) {
			t+=w[i];
		}
		
		lnum_from(aa, t);
		lnum_mul(aa, m);
		lnum_mul(aa, b[i]);
		
		long long k = lnum_mod(aa, n);
		
		a = (a + k) % n;
		//a = (a + t * m % n * b[i] % n) % n;
	}
	//while (a < 0) a += n;
	return a;
}
#undef int

void work() {
	long long mm, n, k;
	cin >> mm >> n >> k;
	for (int i = 0; i < k; i++) {
		cin >> m[i];
		a[i] = lucas(mm, n, m[i]);
	}
	cout << china(a, m, k) << endl;
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		work();
	}
}
/*
 4
 10000000000 99000000 10
 2 3 5 7 13 17 19 23 29 37
 
 
 10000000000 99 4
 21487 21491 21493 100019
 
 10000000000 99 4
 21487 21491 21493 10039
 
 10000000000 99 5
 21487 21491 21493 10039 7
 
 444583918196278671
 
 10000000000 99 3
 21487 21491 100019
 444583918196278671
 
 10000000000 99 3
 21487 21491 21493
 
 
 10000000000 99 3
 101 103 107
 
 
 10000000000 99 10
 2 3 5 7 13 17 19 23 29 37
 */
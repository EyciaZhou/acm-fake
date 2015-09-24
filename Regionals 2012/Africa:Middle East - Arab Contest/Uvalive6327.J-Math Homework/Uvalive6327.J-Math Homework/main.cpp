//
//  main.cpp
//  fake4.j
//
//  Created by eycia on 31/7/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

//60^(MOD-2) % MOD = 616666671
const long long mu  = 616666671;
const long long MOD = 1000000007;

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

bool mm[70];

int main(int argc, const char * argv[]) {
	int t;
	cin >> t;
	
	while (t--) {
		long long n;
		string st;
		
		cin >> n >> st;
		
		long long tot = 0;
		for (int k = 1; k <= 60; k++) {
			bool b = true;
			for (int i = 0; i < 6; i++) {
				if (st[i] == '0' && (k % (i+1) == 0)) {
					b = false;
				}
				if (st[i] == '1' && (k % (i+1) != 0)) {
					b = false;
				}
			}
			mm[k%60] = b;
			if (b) tot++;
		}
		
		long long r = exp(10, n, 60);
		long long d = ((exp(10, n, MOD) + MOD - r) * mu) % MOD;
		long long ans = 0;
		
		//cout << r << " " << d  << endl;
		
		for (int i = 0; i < r; i++) {
			if (mm[i]) ans++;
		}
		
		cout << (ans + d * tot) % MOD << endl;
	}
}

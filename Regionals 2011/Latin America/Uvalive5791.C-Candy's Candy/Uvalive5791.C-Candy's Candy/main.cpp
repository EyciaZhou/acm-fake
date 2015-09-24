//
//  main.cpp
//  Uvalive5791.C-Candy's Candy
//
//  Created by eycia on 23/8/15.
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

long long a[100005];

vector<long long> vec;

inline long long gcd(long long a, long long b) {
	if (a == 0 || b == 0) return max(a, b);
	return __gcd(a, b);
}

int main(int argc, const char * argv[]) {
	int n;
	while (scanf("%d", &n), n) {
		long long mi = 0x7fffffff, ma = 0;
		long long tot = 0;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &a[i]);
			mi = min(mi, a[i]);
			ma = max(ma, a[i]);
			tot += a[i];
		}
		
		sort(a, a+n);
		
		long long g = 0;
		
		for (int i = 1; i < n; i++) {
			if (a[i] - a[i-1] != 0) {
				g = gcd(g, a[i]-a[i-1]);
			}
		}
		
		long long ans = 0;
		
		vec.clear();
		
		for (long long i = 2; i <= sqrt(tot); i++) {
			if (tot % i == 0) {
				vec.push_back(i);
				if (i * i != tot) {
					vec.push_back(tot/i);
				}
			}
		}
		
		for (int j = 0; j < vec.size(); j++) {
			long long i = vec[j];
			if (i % n != 0) continue;
			//i 一包的大小
			
			if (g % i != 0) continue;
			
			long long each = i / n;
			long long num = mi - i - i/n;
			
			if (num < 0) continue;
			long long ver = n * num;
			//num = i * a + each * b ; a = 0
			if (num % each != 0) continue;
			
			ans += (ver / i) / (n) + 1;
		}
		
		cout << ans << endl;
	}
}

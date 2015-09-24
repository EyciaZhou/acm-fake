//
//  main.cpp
//  ksm
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

int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Hello, World!\n";
    return 0;
}

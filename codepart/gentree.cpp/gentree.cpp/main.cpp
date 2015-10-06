//
//  main.cpp
//  gentree.cpp
//
//  Created by eycia on 5/10/15.
//  Copyright © 2015 eycia. All rights reserved.
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

const int mxn = 100005;

int aa[mxn];

int
randint(int l, int r) { //include
	return rand() % (r-l+1) + l;
}

void gentree(int n) {
	for (int i = 2; i <= n; i++) {
		aa[i] = randint(1, i-1);
	}
	for (int i = 2; i <= n; i++) {
		cout << aa[i] << " ";
	}
	cout << endl;
}

void gentree2(int n) {
	for (int i = 2; i <= n; i++) {
		aa[i] = i-1;
	}
	for (int i = 2; i <= n; i++) {
		cout << aa[i] << " ";
	}
	cout << endl;
}

#define mx 100000

int main(int argc, const char * argv[]) {
	freopen("/Users/eycia/i", "w", stdout);
	for (int i = 0; i < 8; i++) {
		int n = randint((int)(0.9*mx), mx);
		int m = randint((int)(0.9*mx), mx);
		printf("%d %d\n", n, m);
		if (i == 7) {
			gentree2(n);
			gentree(n);
		} else {
			gentree(n);
			gentree(n);
		}
		for (int i = 0; i < m; i++) {
			printf("%d %d\n", randint(1, n), randint(1, n));
		}
	}
}

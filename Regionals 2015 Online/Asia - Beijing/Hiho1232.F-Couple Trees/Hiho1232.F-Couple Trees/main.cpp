//
//  main.cpp
//  Hiho1232.F-Couple Trees
//
//  Created by eycia on 23/9/15.
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

int f1[100005];
int f2[100005];

int n, q;

void work() {
	for (int i = 2; i <= n; i++) {
		scanf("%d", &f1[i]);
	}
	for (int i = 2; i <= n; i++) {
		scanf("%d", &f2[i]);
	}
	f1[1] = 0;
	f2[1] = 0;
	int k = 0;
	int l, r;
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &l, &r);
		l = (l+k)%(n)+1;
		r = (r+k)%(n)+1;
		int lc = 0, rc = 0;
		while (l!=r) {
			if (l > r) {
				l = f1[l];
				lc++;
			} else {
				r = f2[r];
				rc++;
			}
		}
		k = l;
		
		printf("%d %d %d\n", l, lc+1, rc+1);
	}
}

int main(int argc, const char * argv[]) {
	while (scanf("%d %d", &n, &q) != EOF) {
		work();
	}
}

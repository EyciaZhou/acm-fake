//
//  main.cpp
//  Hdu4764.F-Stone
//
//  Created by eycia on 9/9/15.
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
int main(int argc, const char * argv[]) {
	int n, k;
	while (scanf("%d %d", &n, &k) != EOF) {
		if (n == 0 && k == 0) break;
		if ((n-1) % (k+1) == 0) {
			puts("Jiang");
		} else {
			puts("Tang");
		}
	}
}

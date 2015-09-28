//
//  main.cpp
//  Uvalive5814.F-Packing for Holiday
//
//  Created by eycia on 28/9/15.
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

int main(int argc, const char * argv[]) {
	int t, a, b, c;
	scanf("%d", &t);
	for (int ff = 1; ff <= t; ff++) {
		scanf("%d %d %d", &a, &b, &c);
		if (a <= 20 && b <= 20 && c <= 20) {
			printf("Case %d: good\n", ff);
		} else {
			printf("Case %d: bad\n", ff);
		}
	}
}

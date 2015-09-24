//
//  main.cpp
//  Uvalive7035.A-Built with Qinghuai and Ari Factor
//
//  Created by eycia on 18/9/15.
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
	int t, n, tmp;
	scanf("%d", &t);
	for (int ff = 1; ff <= t; ff++) {
		bool f = true;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &tmp);
			f = f && (tmp%3 == 0);
		}
		if (f) {
			printf("Case #%d: Yes\n", ff);
		} else {
			printf("Case #%d: No\n", ff);
		}
	}
}

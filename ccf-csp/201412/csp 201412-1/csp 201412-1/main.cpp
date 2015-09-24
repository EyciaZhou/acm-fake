//
//  main.cpp
//  csp 201412-1
//
//  Created by eycia on 4/9/15.
//  Copyright (c) 2015 eycia. All rights reserved.
//

#include <set>
#include <map>
#include <list>
//#include <tuple>
//#include <ratio>
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

int cnt[1005];

int main(int argc, const char * argv[]) {
	int n, tmp;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &tmp);
		printf("%d ", ++cnt[tmp]);
	}
}

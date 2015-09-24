//
//  main.cpp
//  1002.B-Xiao Ming climbing
//
//  Created by eycia on 12/9/15.
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

char tmp[100];

int mp[55][55];



void work() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%s", tmp);
		for (int j = 1; j <= m; j++) {
			mp[i][j] = tmp[j] - '0';
		}
	}
	
	
}

int main(int argc, const char * argv[]) {
	int t;
	while (t--) {
		work();
	}
}

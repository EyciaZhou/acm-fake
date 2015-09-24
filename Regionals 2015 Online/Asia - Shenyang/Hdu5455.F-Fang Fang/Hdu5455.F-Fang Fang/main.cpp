//
//  main.cpp
//  a2
//
//  Created by eycia on 19/9/15.
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

char tmp[1000005];

int work() {
	scanf("%s", tmp);
	
	int sl = strlen(tmp);
	
	for (int i = 0; i < sl; i++) {
		if (tmp[i] != 'c' && tmp[i] != 'f') {
			return -1;
		}
	}
	
	int i = 0;
	
	for (i = 0; i < sl; i++) {
		if (tmp[i] == 'c') {
			break;
		}
		
		
	}
	
	int star = i;
	
	if (star == sl) {
		return sl / 2 + sl % 2;
	}
	
	rotate(tmp, tmp+star, tmp+sl);
	
	int lst = 0;
	int k = 0;
	
	for (int i = 1; i < sl; i++) {
		if (tmp[i] == 'c') {
			if (i - lst <= 2) {
				return -1;
			}
			k++;
			lst = i;
		}
	}
	
	if (sl - lst <= 2) {
		return -1;
	}
	return k+1;
}

int main(int argc, const char * argv[]) {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		printf("Case #%d: %d\n", i, work());
	}
}

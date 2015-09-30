//
//  main.cpp
//  Uvalive5810.B-Candles
//
//  Created by eycia on 30/9/15.
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

int ones(int i) {
	bitset<10> b(i);
	return b.count();
}

vector<int> nn[12];

bool inc[1<<12][200];

bool judge(int mask, int t1, int t2) {
	int tot = 0;
	
	while (t1 > 0) {
		if (( tot & (1 << (t1%10)) ) != 0) {
			return false;
		}
		tot |= (1 << (t1%10));
		t1/=10;
	}
	while (t2 > 0) {
		if (( tot & (1 << (t2%10)) ) != 0) {
			return false;
		}
		tot |= (1 << (t2%10));
		t2/=10;
	}
	return (mask & tot) == tot;
}


bool ju2(int mask, int t1) {
	int tot = 0;
	
	while (t1 > 0) {
		if (( tot & (1 << (t1%10)) ) != 0) {
			return false;
		}
		tot |= (1 << (t1%10));
		t1/=10;
	}
	return (mask & tot) == tot;
}

void init() {
	for (int i = 0; i < (1<<11); i++) {
		nn[ones(i)].push_back(i);
	}

	for (int mask = 0; mask < (1<<11); mask++) {
		for (int yy = 1; yy <= 100; yy++) {
			for (int t1 = 1; t1 < yy; t1++) {
				inc[mask][yy] |= judge(mask, t1, yy - t1);
			}
			inc[mask][yy] |= ju2(mask, yy);
		}
	}
}

int a[20];

int main(int argc, const char * argv[]) {
	int n;
	
	init();
	int ff = 0;
	while (scanf("%d", &n) != EOF) {
		ff++;
		if (n == 0) break;
		
		printf("Case %d: ", ff);
		
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		bool ok = true;
		int an = 0;
		for (int i = 1; i < 11; i++) {
			for (int k = 0; k < nn[i].size(); k++) {
				int no = nn[i][k];
				ok = true;
				for (int p = 0; p < n; p++) {
					ok &= inc[no][a[p]];
				}
				an = no;
				if (ok) break;
			}
			if (ok) break;
		}
		for (int i = 9; i >= 0; i--) {
			if (bitset<10>(an).test(i)) {
				printf("%d", i);
			}
		}
		puts("");
	}
}

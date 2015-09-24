//
//  main.cpp
//  Uvalive5794.F-File Retrieval
//
//  Created by eycia on 24/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
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

char tmp[10005];

const int N = 10010000;
const int tk = 26, tb = 'a';
long long top, tree[N][tk+1], mk[N];

void init() {
	top = 1;
	memset(tree[0], 0, sizeof(tree[0]));
}

void insert(char *s, long long mask) {
	int rt, nxt;
	for (rt = 0; *s; rt = nxt, ++s, tree[rt][tk] |= mask) {
		nxt = tree[rt][*s - tb];
		if (0 == nxt) {
			tree[rt][*s - tb] = nxt = top;
			//cout << *s << " " << top;
			memset(tree[top], 0, sizeof(tree[top]));
			top++;
		}
	}
}

set<long long> ans;

vector<string> fs;

int main(int argc, const char * argv[]) {
	int f;
	while (scanf("%d", &f), f) {
		//init();
		fs.clear();
		ans.clear();
		for (int i = 0; i < f; i++) {
			scanf("%s", tmp);
			fs.push_back(string(tmp));
		}
		for (int i = 1; i < top; i++) {
			ans.insert(tree[i][tk]);
		}
		cout << ans.size() << endl;
	}
}

//
//  main.cpp
//  Uvalive5792.D-Diccionário Portuñol
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

const int N = 100005, tk = 26, tb = 'a';

struct {
	long long top;
	int tree[N][tk+1], mk[N];

	void init() {
		top = 1;
		memset(tree, 0, sizeof(tree));
	}

	void insert(char *s) {
		int rt, nxt;
		for	(rt = 0; *s; rt = nxt, ++s, tree[rt][tk]=1) {
			nxt = tree[rt][*s - tb];
			if (0 == nxt) {
				tree[rt][*s - tb] = nxt = top;
				memset(tree[top], 0, sizeof(tree[top]));
				top++;
			}
		}
	}
	
} trie1, trie2;

char tmp[10005];
long long k1[30], k2[30];

int main(int argc, const char * argv[]) {
	int n, m;
	while (scanf("%d %d", &n, &m), n+m) {
		trie1.init();
		trie2.init();
		for (int i = 0; i < n; i++) {
			scanf("%s", tmp);
			trie1.insert(tmp);
		}
		for (int i = 0; i < m; i++) {
			scanf("%s", tmp);
			reverse(tmp, tmp+strlen(tmp));
			trie2.insert(tmp);
		}
		
		memset(k1, 0, sizeof(k1));
		memset(k2, 0, sizeof(k2));
		
		for (int i = 1; i < trie1.top; i++) {
			for (int j = 0; j < 26; j++) {
				if (trie1.tree[i][j] != 0) {
					k1[j]++;
				}
			}
		}
		
		for (int i = 1; i < trie2.top; i++) {
			for (int j = 0; j < 26; j++) {
				if (trie2.tree[i][j] != 0) {
					k2[j]++;
				}
			}
		}
		
		long long tot = 0;
		for (int j = 0; j < 26; j++) {
			tot += k1[j] * k2[j];
		}
		cout << (trie1.top-1) * (trie2.top-1) - tot << endl;
	}
}

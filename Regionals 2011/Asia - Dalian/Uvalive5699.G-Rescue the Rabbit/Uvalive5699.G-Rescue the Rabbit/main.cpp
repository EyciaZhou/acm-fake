//
//  main.cpp
//  Uvalive5699.G-Rescue the Rabbit
//
//  Created by eycia on 8/9/15.
//  Copyright (c) 2015 eycia. All rights reserved.
//

#include <set>
#include <map>
#include <list>
#include <tuple>
#include <ratio>
#include <cmath>
#include <queue>
#include <ctime>
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

char tmp[1000];

int f[2][1024][1005];

const int inf = 0x3f3f3f3f;

const int N = 2005;
const int tk = 4, tb = 'a';
int top, tree[N][tk+1];
int m[N], fail[N];

void init() {
	top = 1;
	memset(m, 0, sizeof(m));
	memset(tree, 0, sizeof(tree));
	memset(fail, 0, sizeof(fail));
}

void insert(char *s, int va, int ms) {
	int rt, nxt;
	for (rt = 0; *s; rt = nxt, ++s) {
		nxt = tree[rt][*s - tb];
		if (0 == nxt) {
			tree[rt][*s - tb] = nxt = top;
			memset(tree[top], 0, sizeof(tree[top]));
			top++;
		}
	}
	m[rt] = (1 << ms);
}

queue<int> q;

void genfa() {
	fail[0] = 0;
	q.push(0);
	while (!q.empty()) {
		int k = q.front();
		q.pop();
		
		for (int i = 0; i < tk; i++) {
			if (tree[k][i] != 0) {
				
				int f = fail[k];
				
				while (f != 0) {
					if (tree[f][i] != 0) {
						break;
					}
					f = fail[f];
				}
				
				if (k != 0 && tree[f][i] != 0) {
					f = tree[f][i];
				}
				
				fail[tree[k][i]] = f;
				m[tree[k][i]] |= m[f];
				
				q.push(tree[k][i]);
			}
		}
	}
}

int getnext(int now, int k) {
	int f = now;
	
	while (f != 0 && tree[f][k] == 0) {
		f = fail[f];
	}
	if (tree[f][k] != 0) {
		f = tree[f][k];
	}
	return f;
}

char inline tr(char o) {
	switch (o) {
		case 'A':
			return 'a';
			break;
		case 'T':
			return 'b';
			break;
		case 'C':
			return 'c';
			break;
		case 'G':
			return 'd';
			break;
	}
	return 'a';
}

int an[1024];
int v[100];

int main(int argc, const char * argv[]) {
	freopen("/Users/eycia/i", "r", stdin);
	int n, l, va;
	while (scanf("%d %d", &n, &l) != EOF) {
		memset(f, false, sizeof(f));
		init();
		for (int i = 0; i < n; i++) {
			scanf("%s %d", tmp, &v[i]);
		
			int sl = strlen(tmp);
		
			transform(tmp, tmp+sl, tmp, tr);
		
			if (strlen(tmp) > l) {
				continue;
			}
			insert(tmp, va, i);
		}
	
		genfa();

		f[0][0][0] = true;
		int to = (1 << n) - 1;
		int mx = -1;
		
		for (int i = 0; i < n; i++) {
			int msk = (1 << i);
			for (int m = 0; m < msk; m++) {
				an[m|msk] = an[m]+v[i];
			}
		}
		
		for (int i = 1; i <= l; i++) {
			for (int mask = 0; mask <= to; mask++) {
				for (int now = 0; now <= top; now++) {
					f[i&1][mask][now]=false;
				}
			}
			for (int mask = 0; mask <= to; mask++) {
				for (int now = 0; now <= top; now++) {
					if (f[(i+1)&1][mask][now]) {
						for (int k = 0; k < 4; k++) {
							int nxt = getnext(now, k);
							f[i&1][mask | m[nxt]][nxt] = true;
							mx = max(mx, an[mask | m[nxt]]);
						}
					}
				}
			}
		}
		if (mx == -1) {
			puts("No Rabbit after 2012!");
		} else {
			printf("%d\n", mx);
		}
	}
}

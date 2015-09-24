//
//  main.cpp
//  a1
//
//  Created by eycia on 13/9/15.
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

struct {
	vector<vector<int> > k;
	vector<int> aa;
	void init(vector<int > a) {
		k.clear();
		aa = a;
		int mn = a.size();
		int ml = (int)(log(mn) / log(2) + 5);
		for (int i = 0; i < ml; i++) {
			k.push_back(vector<int>());
		}
		for (int i = 0; i < mn; i++) {
			k[0].push_back(i);
		}
		for (int j = 1; j < ml; j++) {
			for (int i = 0; i < mn; i++) {
				if ((1 << (j-1))+i < mn) {
					if (a[k[j-1][i]] > a[k[j-1][(1 << (j-1))+i]]) {
						k[j].push_back(k[j-1][i]);
					} else {
						k[j].push_back(k[j-1][(1 << (j-1))+i]);
					}
				} else {
					k[j].push_back(k[j-1][i]);
				}
			}
		}
	}
	
	int query(int l, int r) {
		if (l > r) swap(r, l);
		int len = r - l + 1;
		int c = int(log(len) / log(2));
		if (aa[k[c][l]] > aa[k[c][r-(1<<c)+1]]) {
			return k[c][l];
		}
		return k[c][r-(1<<c)+1];
	}
} rmq_st;

vector<int>  vec;

int main(int argc, const char * argv[]) {
	int t, tmp;
	scanf("%d", &t);
	for (int i = 0; i <t; i++) {
		int n;
		vec.clear();
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &tmp);
			vec.push_back(tmp);
		}
		rmq_st.init(vec);
		
		int q, l, r;
		scanf("%d", &q);
		
		for (int i = 0; i < q; i++) {
			scanf("%d %d", &l, &r);
			l--; r--;
			printf("%d\n", vec[rmq_st.query(l, r)]);
		}
	}
}

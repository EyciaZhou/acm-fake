//
//  main.cpp
//  Uvalive5793.E-Elecrical Pollution
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

map<pair<int, int>, int> ps;
vector<pair<pair<int, int>, int> > p;
set<int> xx;

#define mp make_pair

int main(int argc, const char * argv[]) {
	int m, q, x, y, a;
	while (scanf("%d %d", &m, &q), m + q) {
		ps.clear();
		p.clear();
		xx.clear();
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &a);
			p.push_back(mp(mp(x, y), a));
			p.push_back(mp(mp(y, x), a));
			xx.insert(x);
			xx.insert(y);
			ps[make_pair(x, y)] = a;
			ps[make_pair(y, x)] = a;
		}
		
		sort(p.begin(), p.end());
		p.erase(unique(p.begin(), p.end()), p.end());
		
		for (int i = 0; i < q; i++) {
			scanf("%d %d", &x, &y);
			pair<int, int> po = make_pair(x, y);
			if (ps.find(po) == ps.end()) {
				bool find = false;
				int ans = 0;
				if (xx.find(po.first) != xx.end() && xx.find(po.second) != xx.end())
				for (int j = 0; j < p.size(); j++) {
					if (find) break;
					
					pair<pair<int, int>, int> p2 = p[j];
					
					pair<int, int> pb = make_pair(p2.first.first, po.second), pc = make_pair(po.first, p2.first.second);
					if (ps.find(pb) != ps.end()) {
						if (ps.find(pc) != ps.end()) {
							ans = ps[pb] + ps[pc] - p2.second;
							find = true;
							break;
						}
					}
				}
				if (find) {
					printf("%d\n", ans);
				} else {
					puts("*");
				}
				
			} else {
				printf("%d\n", ps[po]);
			}
		}
		puts("-");
	}
    return 0;
}

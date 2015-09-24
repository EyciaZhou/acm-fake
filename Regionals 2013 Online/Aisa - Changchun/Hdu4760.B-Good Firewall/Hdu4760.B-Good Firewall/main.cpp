//
//  main.cpp
//  Hdu4760.B-Good Firewall
//
//  Created by eycia on 10/9/15.
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
	unsigned int net;
	unsigned int mask;
	bool forb;
	int p;
} sn[70000];

vector<int> ns[256];
vector<int> pol[1500];
char o[10];

bitset<1050> t1, t2;

int mem=0;

unsigned int rd() {
	unsigned int t[4];
	unsigned int tot = 0;
	scanf("%u.%u.%u.%u", &t[0], &t[1], &t[2], &t[3]);
	for (int i = 0; i < 4; i++) {
		tot <<= 8;
		tot += t[i];
	}
	return tot;
}

unsigned int tmsk(int m) {
	unsigned int tot = 0;
	for (int i = 0; i < m; i++) {
		tot <<= 1;
		tot |= 1;
	}
	for (int i = m; i < 32; i++) {
		tot <<= 1;
	}
	return tot;
}

bool judge(unsigned nt, unsigned int ny) {
	t1 = bitset<1050>(0);
	t2 = bitset<1050>(0);
	
	int suf = nt >> 24;
	for (int i = 0; i < ns[suf].size(); i++) {
		if ((nt & sn[ns[suf][i]].mask) == sn[ns[suf][i]].net) {
			if (!sn[ns[suf][i]].forb) {
				t1.set(sn[ns[suf][i]].p);
			}
		}
	}
	
#define nt ny
	suf = nt >> 24;
	for (int i = 0; i < ns[suf].size(); i++) {
		if ((nt & sn[ns[suf][i]].mask) == sn[ns[suf][i]].net) {
			if (!sn[ns[suf][i]].forb) {
				t2.set(sn[ns[suf][i]].p);
			}
		}
	}
#undef nt
	
	t1.operator&=(t2);
	return t1.any();
}

int main(int argc, const char * argv[]) {
	int id, n, m;
	while (scanf("%s", o) != EOF) {
		if (o[0] == 'E') {
			scanf("%d %d", &id, &n);
			for (int i = 0; i < n; i++) {
				sn[mem].net = rd();
				scanf("/%d", &m);
				sn[mem].mask = tmsk(m);
				sn[mem].net &= sn[mem].mask;
				sn[mem].forb = false;
				sn[mem].p = id;
				
				pol[id].push_back(mem);
				ns[sn[mem].net >> 24].push_back(mem);
				mem++;
			}
		} else if (o[0] == 'D') {
			scanf("%d", &id);
			for (int i = 0; i < pol[id].size(); i++) {
				sn[pol[id][i]].forb = true;
			}
		} else if (o[0] == 'F') {
			
			unsigned lnt = rd(), rnt = rd();
			if (judge(lnt, rnt)) {
				puts("F");
			} else {
				puts("D");
			}
			
		}
	}
}

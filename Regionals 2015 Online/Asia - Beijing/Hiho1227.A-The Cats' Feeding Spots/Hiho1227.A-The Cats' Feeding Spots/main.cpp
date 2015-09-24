//
//  main.cpp
//  a1
//
//  Created by eycia on 20/9/15.
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

struct po {
	double x, y;
	po(double x, double y) : x(x), y(y) {}
	po() {}
};

po cp;

inline double dist(const po &l, const po &r) {
	
	return sqrt((l.x-r.x)*(l.x-r.x)+(l.y-r.y)*(l.y-r.y));
}

inline double dist2(const po &l, const po &r) {
	
	return (l.x-r.x)*(l.x-r.x)+(l.y-r.y)*(l.y-r.y);
}

inline bool operator < (const po &l, const po &r) {
	return dist2(l, cp) < dist2(r, cp);
}

vector<po> ps;
vector<po> p2;

void pr(po &p, string s) {
	cout << s << "x: " <<p.x << "   " << "y: " << p.y << endl;
}

long long work() {
	int n, m;
	ps.clear();
	p2.clear();
	double ll, rr;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%lf %lf", &ll, &rr);
		ps.push_back(po(ll, rr));
		p2.push_back(po(ll, rr));
	}
	
	if (m > n) {
		return -1;
	}
	
	long long mr = 0x7fffffff;
	
	for (int c = 0; c < n; c++) {
		
		cp = p2[c];
		
		//sort(ps.begin(), ps.end());
		
		sort(ps.begin(), ps.end());
		
		long long di = dist(cp, ps[m-1])+1;
		
		
		if (n != m) {
			if (dist2(cp, ps[m]) <= di*di ) {
				continue;
			}
		}
		
		mr = min(mr, di);
	}
	
	if (mr == 0x7fffffff) {
		return -1;
	}
	return mr;
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	
	for (int i = 0; i < t; i++) {
		cout << work() << endl;
	}
}
/*
 
 4
 3 2
 0 0
 -1 0
 1 0
 
 3 2
 0 0
 1.41421357 1.41421357
 1 0
 
 
 3 3
 0 0
 -1 -1
 100 100
 
 4 3
 1000 1000
 -1000 -1000
 1000 -1000
 -1000 1000
 */

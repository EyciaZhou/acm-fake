//
//  main.cpp
//  a1
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

vector<pair<long long ,int> > t1, t2;
long long seg, two;

priority_queue<pair<long long ,int> > q1, q2;
priority_queue<pair<long long ,int>, vector<pair<long long ,int> >, greater<pair<long long ,int> > > p1, p2;

void work(int ff) {
	int n;
	long long a, b;
	
	while (!q1.empty()) q1.pop();
	while (!q2.empty()) q2.pop();
	while (!p1.empty()) p1.pop();
	while (!p2.empty()) p2.pop();
	t1.clear();
	t2.clear();
	
	scanf("%d %I64d %I64d", &n, &a, &b);
	
	for (int i = 0; i < n; i++) {
		scanf("%I64d", &seg);
		two = seg * seg;
		
		q1.push(make_pair(seg, i));
		q2.push(make_pair(two, i));
		
		p1.push(make_pair(seg, i));
		p2.push(make_pair(two, i));
		
		if (q1.size() > 2) q1.pop();
		if (q2.size() > 2) q2.pop();
		if (p1.size() > 2) p1.pop();
		if (p2.size() > 2) p2.pop();
	}
	
	for (int i = 0; i < 2; i++) {
		t1.push_back(q1.top());
		q1.pop();
		
		t1.push_back(p1.top());
		p1.pop();
	}
	
	for (int i = 0; i < 2; i++) {
		t2.push_back(q2.top());
		q2.pop();
		
		t2.push_back(p2.top());
		p2.pop();
	}
	
	long long mx = -1;
	bool flag = false;
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (t2[i].second != t1[j].second) {
				if (!flag || mx < a*t2[i].first+b*t1[j].first) {
					mx = a*t2[i].first+b*t1[j].first;
					flag = true;
				}
			}
		}
	}
	
	printf("Case #%d: %I64d\n", ff, mx);
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		work(i);
	}
}
/*
 2
 5 1 1
 0 0 0 0 0
 2 1 1
 -1 -1
 */
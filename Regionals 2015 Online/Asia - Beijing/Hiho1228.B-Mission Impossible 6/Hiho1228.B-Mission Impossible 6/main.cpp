//
//  main.cpp
//  Hiho1228.B-Mission Impossible 6
//
//  Created by eycia on 22/9/15.
//  Copyright © 2015 eycia. All rights reserved.
//
// two stack version
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

stack<char> l, r;
stack<char> cl, cr;
vector<char> tmp;

char o[1000000];

stack<char> tl, tr;

void work() {
	while (!l.empty()) l.pop();
	while (!r.empty()) r.pop();
	while (!cl.empty()) cl.pop();
	while (!cr.empty()) cr.pop();
	tmp.clear();
	
	int lim;
	
	scanf("%d", &lim);

	int sl = 0x7fffffff;
	
	int mode = 1, star = 0;
	bool c = false;
	
	scanf("%s", o);
	
	sl = strlen(o);
	
	for (int i = 0; i < sl; i++) {
		
		if (c) {
			if (o[i] != 'L' && o[i] != 'R' && o[i] != 'D' && o[i] != 'C') {
				c = false;
			}
		}
		switch (o[i]) {
			case 'L':
				if (l.size() > 0) {
					if (c) {
						if (!cl.empty()) {
							cl.pop();
						} else {
							cr.push(l.top());
						}
					}
					
					r.push(l.top());
					l.pop();
				}
				break;
				
			case 'R':
				if (r.size() > 0) {
					if (c) {
						if (!cr.empty()) {
							cr.pop();
						} else {
							cl.push(r.top());
						}
					}
					
					l.push(r.top());
					r.pop();
				}
				break;
			
			case 'S':
				mode = 1-mode;
				break;
				
			case 'B':
				if (l.size() > 0) {
					l.pop();
				}
				break;
				
			case 'D':
				if (c) {
					if (star <= l.size()) {
						while (star != l.size()) {
							l.pop();
						}
					} else {
						while (star != l.size()) {
							r.pop();
							star--;
						}
					}
					c=false;
				} else {
					if (!r.empty()) r.pop();
				}
				break;
				
			case 'C' :
				if (c) {
					tmp.clear();
					while (!cl.empty()) {
						cr.push(cl.top());
						cl.pop();
					}
					while (!cr.empty()) {
						tmp.push_back(cr.top());
						cr.pop();
					}
					c = false;
				} else {
					c = true;
					star = l.size();
					while (!cl.empty()) cl.pop();
					while (!cr.empty()) cr.pop();
				}
				
				break;
				
			case 'V' :
				if (mode == 1 && l.size() + r.size() + tmp.size() > lim) {
					continue;
				}
				
				if (mode == 0 && l.size() + tmp.size() > lim) {
					continue;
				}
				
				for (int i = 0; i < tmp.size(); i++) {
					if (mode == 1 || r.size() == 0) {
						if (l.size() + r.size() < lim) {
							l.push(tmp[i]);
						}
					} else {
						r.pop();
						l.push(tmp[i]);
					}
				}
				break;
				
			default:
				if (o[i] < 'a' || o[i] > 'z') continue;
				if (mode == 1 || r.size() == 0) {
					if (l.size() + r.size() < lim) {
						l.push(o[i]);
					}
				} else {
					r.pop();
					l.push(o[i]);
				}
				break;
		}
	}
	if (l.size() == 0 && r.size() == 0) {
		puts("NOTHING");
		return ;
	}
	while (!l.empty()) {
		r.push(l.top());
		l.pop();
	}
	while (!r.empty()) {
		putchar(r.top());
		r.pop();
	}
	puts("");
}

int main(int argc, const char * argv[]) {
	//freopen("/Users/eycia/i", "r", stdin);
	//freopen("/Users/eycia/o", "w", stdout);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		work();
	}
}
/*
abcCLLCRRRBLLCV
abcCLLCRRRBLCV
abcCLLCRRRBLCSV
 
qonvLBzDVxVmLLrCelDmVyVCSRoDRRVDyrkVDCmLDRCBxLRcS
 */
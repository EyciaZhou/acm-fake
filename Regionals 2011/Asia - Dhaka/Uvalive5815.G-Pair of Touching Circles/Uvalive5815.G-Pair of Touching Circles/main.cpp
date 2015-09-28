//
//  main.cpp
//  Uvalive5815.G-Pair of Touching Circles
//
//  Created by eycia on 28/9/15.
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

#define eps 1e-9;

vector<pair<int, int> > ds;
//map<pair<int, int>, long long> cnt;

int cnt[1005][1005];

void init() {
	for (int i = 0; i <= 1000; i++) {
		for (int j = i + 1; j <= 1000; j++) {
			int k = sqrt(i*i+j*j);
			
			if (i*i+j*j != k*k) continue;
			
			for (int r1 = 1; r1 <= k/2; r1++) {
				int r2 = k - r1;
				
				int hi = max(max(i + r1 + r2, r1 + r1), r2+r2);
				int wi = max(max(j + r1 + r2, r2 + r2), r1+r1);
				
				if (hi > 1000 || wi > 1000) continue;
				
				
				if (r1 == r2 || i == 0) {
					if (r1 == r2 && i == 0) {
						cnt[hi][wi]++;
						cnt[wi][hi]++;
					} else {
						cnt[hi][wi]+=2;
						cnt[wi][hi]+=2;
					}
					//ds.push_back(make_pair(hi, wi));
				} else {
					
					cnt[hi][wi]+=4;
					cnt[wi][hi]+=4;
					//ds.push_back(make_pair(hi, wi));
					//ds.push_back(make_pair(wi, hi));
					//cout << wi << " " << hi << " " << r1 << " " << r2 << " " << i << " " << j << endl;
				}
			}
		}
	}
}

long long c[1005][1005];

void genc() {
	memset(c, 0, sizeof(c));
	c[1][1] = 1;
	for (int i = 2; i <= 1003; i++) {
		for (int j = 1; j <= i; j++) {
			c[i][j] = (c[i-1][j] + c[i-1][j-1]);
		}
	}
	for (int i = 1; i <= 54; i++) {
		for(int j = 1; j <= i; j++) {
			c[i-1][j-1] = c[i][j];
		}
	}
}

void work(int ff) {
	int hh, ww;
	scanf("%d %d", &hh, &ww);
	
	long long tot = 0;
	
	for (int hi = 2; hi <= hh; hi++) {
		for (int wi = 2; wi <= ww; wi++) {
			long long tmp = cnt[hi][wi];
			
			tot += (hh-hi+1)*(ww-wi+1)*tmp;
			
		}
	}
	printf("Case %d: %lld\n", ff, tot);
}

int main(int argc, const char * argv[]) {
	int t;
	init();
	genc();
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		work(i);
	}
}

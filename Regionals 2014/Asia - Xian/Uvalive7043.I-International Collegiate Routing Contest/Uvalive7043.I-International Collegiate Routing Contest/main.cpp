//
//  main.cpp
//  Uvalive7043.I-International Collegiate Routing Contest
//
//  Created by eycia on 4/10/15.
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

int lc[1000005];
int rc[1000005];
int dep[1000005];
long long sl[1000005];
long long sr[1000005];
bool mask[1000005];
int mem;

void init() {
	sl[0] = 0;
	sr[0] = 4294967295;
	mem = 0;
	dep[0] = 0;
	memset(mask, false, sizeof(mask));
	memset(lc, -1, sizeof(lc));
	memset(rc, -1, sizeof(rc));
}

void inline create(int t, int &r, long long st) {
	if (r < 0) {
		r = ++mem;
		dep[r] = dep[t]+1;
		sl[r] = st+sl[t];
		sr[r] = st+(sl[t]+sr[t])/2;
	}
}

void insert(int t, long long lb, long long rb, long long ll, long long rr) {
	if (lb == ll && rb == rr) {
		mask[t] = true;
		return;
	}
	
	long long mid = (lb+rb)/2;
	
	if (rr <= mid) {
		create(t, lc[t], 0);
		insert(lc[t], lb, mid, ll, rr);
	} else if (ll > mid) {
		create(t, rc[t], (sl[t]+sr[t])/2+1 - sl[t]);
		insert(rc[t], mid+1, rb, ll, rr);
	} else {
		create(t, lc[t], 0);
		create(t, rc[t], (sl[t]+sr[t])/2+1 - sl[t]);
		insert(lc[t], lb, mid, ll, mid);
		insert(rc[t], mid+1, rb, mid+1, rb);
	}
}

vector<pair<long long, int> > ans;

void dfs(int t) {
	if (mask[t]) return;
	
	if (lc[t] < 0 && rc[t] < 0) {
		ans.push_back(make_pair(sl[t], dep[t]));
		return;
	}
	
	if (lc[t] >= 0) {
		dfs(lc[t]);
	} else {
		ans.push_back(make_pair(sl[t], dep[t]+1));
	}
	
	if (rc[t] >= 0) {
		dfs(rc[t]);
	} else {
		ans.push_back(make_pair((sl[t]+sr[t])/2+1, dep[t]+1));
	}
}

long long ms[4];

long long inline lowbit(long long x) {
	return x & (-x);
}

void fm(long long l, int r) {
	for (int i = 0; i < 3; i++) {
		ms[i] = l%256;
		l/=256;
	}
	ms[3] = l;
	printf("%lld.%lld.%lld.%lld/%d\n", ms[3], ms[2], ms[1], ms[0], r);
}

struct pp{
	long long ip;
	long long mask;
	pp(long long l, long long r): ip(l), mask(r) {}
};

long long m2m[50];

pp rd() {
	for (int i = 3; i >= 0; i--) {
		scanf("%lld", &ms[i]);
		getchar();
	}
	
	long long tot = 0, m;
	
	for (int i = 0; i < 4; i++) {
		tot += ((long long)(1) << (i*8)) * ms[i];
	}
	scanf("%lld", &m);
	
	return pp(tot, m2m[m]);
}


void work() {
	int n;
	pp p(0, 0);
	init();
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		p = rd();
		long long l = p.ip & p.mask;
		long long r = (p.ip & p.mask) + lowbit(p.mask) - 1;
		insert(0, 0, 4294967295, l, r);
	}
	
	ans.clear();
	dfs(0);
	printf("%lu\n", ans.size());
	for (int i = 0; i < ans.size(); i++) {
		fm(ans[i].first, ans[i].second);
	}
}

int main() {
	long long all = ((long long)(1) << (33)) - 1;
	m2m[32] = all;
	for (int i = 31; i >= 0; i--) {
		m2m[i] = (m2m[i+1] << 1) & all;
	}
	
	int n;
	scanf("%d", &n);
	for (int ff = 1; ff <= n; ff++) {
		printf("Case #%d:\n", ff);
		work();
	}
}

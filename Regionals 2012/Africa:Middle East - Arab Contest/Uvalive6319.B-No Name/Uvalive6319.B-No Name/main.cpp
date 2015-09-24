//
//  main.cpp
//  fake4.b
//
//  Created by eycia on 31/7/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <list>
#include <cstdlib>
#include <cmath>
using namespace std;

struct node {
	int l, r;
	int p;
	char v;
	int ln;
};

struct treap {
	node ns[400000];
	int m;
	int root;
	
	inline void r_ro(int &r) {
		int t = r;
		r = ns[r].l;
		ns[t].l = ns[r].r;
		ns[r].r = t;
		ns[t].ln = ns[t].ln - ns[r].ln - 1;
	}
	
	inline void l_ro(int &r) {
		int t = r;
		r = ns[r].r;
		ns[t].r = ns[r].l;
		ns[r].l = t;
		ns[r].ln = ns[r].ln + ns[t].ln + 1;
	}
	
	
	void insert_rank(int &r, int rank, char k) {
		if (r == -1) {
			m++;
			ns[m].l = ns[m].r = -1;
			ns[m].p = rand();
			ns[m].v = k;
			ns[m].ln = 0;
			r = m;
		} else if (rank <= ns[r].ln) {
			insert_rank(ns[r].l, rank, k);
			ns[r].ln++;
			if (ns[ns[r].l].p > ns[r].p) {
				r_ro(r);
			}
		} else {
			insert_rank(ns[r].r, rank-ns[r].ln-1, k);
			if (ns[ns[r].r].p > ns[r].p) {
				l_ro(r);
			}
		}
	}
	
	void pr(int r, int ll, int rr) {
		if (rr < ll) return;
		if (ll < 0 || rr < 0) return;
		if (r == -1) {
			return ;
		} else {
			if (ns[r].ln > rr || ns[r].ln < ll) {
				//cout << "i1" << endl;
				if (ns[r].ln > rr) {
					pr(ns[r].l, ll, rr);
				}
				if (ns[r].ln < ll) {
					pr(ns[r].r, ll-ns[r].ln-1, rr-ns[r].ln-1);
				}
			} else {
				//cout << "i2" << endl;
				pr(ns[r].l, ll, ns[r].ln);
				putchar(ns[r].v);
				pr(ns[r].r, 0, rr-ns[r].ln-1);
			}
		}
	}
	
	
	
	void init() {
		memset(ns, 0, sizeof(ns));
		m = -1;
		root = -1;
	}
};

treap tp;

char ori[400000];
char tmp[10];
char ts[400000];

int main(int argc, const char * argv[]) {
	int t;
	int inde, il, ir, lo;
	scanf("%d", &t);
	while (t--) {
		tp.init();
		scanf("%s", ori);
		lo = strlen(ori);
		for (int i = lo-1; i >= 0; i--) {
			tp.insert_rank(tp.root, 0, ori[i]);
		}
		while (true) {
			scanf("%s", tmp);
			if (tmp[0] == 'I') {
				scanf("%s %d", ts, &inde);
				int le = strlen(ts);
				for (int i = le-1; i >= 0; i--) {
					tp.insert_rank(tp.root, inde, ts[i]);
				}
			}
			if (tmp[0] == 'P') {
				scanf("%d %d", &il, &ir);
				tp.pr(tp.root, il, ir);
				cout << endl;
			}
			if (tmp[0] == 'E') {
				break;
			}
		}
	}
}
/*
 acm
 I ac 3
 P 0 3
 I x 3
 I xxxx 6
 I pc 6
 P 0 11
 END
 
 1
 acm
 I ac 3
 P 0 3
 I x 3
 I xxxx 6
 I pc 6
 P 0 11
 END
 */
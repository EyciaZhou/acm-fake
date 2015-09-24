//
//  main.cpp
//  a6
//
//  Created by eycia on 14/9/15.
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

struct node {
	int l, r;
	int p; //random number
	int v; //value
	int ln; //leftnumber
};

struct treap {
	node ns[1005];
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
	
	void insert(int &r, int key) {
		if (r == -1) {
			m++;
			ns[m].l = ns[m].r = -1;
			ns[m].p = rand();
			ns[m].v = key;
			ns[m].ln = 0;
			r = m;
		} else if (key < ns[r].v) {
			insert(ns[r].l, key);
			if (ns[ns[r].l].p > ns[r].p) {
				r_ro(r);
			}
		} else {
			insert(ns[r].r, key);
			if (ns[ns[r].r].p > ns[r].p) {
				l_ro(r);
			}
		}
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
	
	bool remove(int &r, int key) {
		if (r == -1) {
			return false;
		}
		if (key <= ns[r].v) {
			bool bl = remove(ns[r].l, key);
			if (!bl && key == ns[r].v) {
				if (ns[r].l == -1) {
					r = ns[r].r;
				} else if (ns[r].r == -1) {
					r = ns[r].l;
				} else if (ns[r].l == -1 && ns[r].r == -1) {
					r = -1;
				} else {
					if (ns[ns[r].l].p > ns[ns[r].r].p) {
						r_ro(r);
						remove(ns[r].r, key);
					} else {
						l_ro(r);
						remove(ns[r].l, key);
					}
				}
			}
			return true;
		} else {
			return remove(ns[r].r, key);
		}
	}
	
	int find(int r, int key) {
		if (r == -1) {
			return -1;
		}
		if (key == ns[r].v) {
			return r;
		} else if (key <= ns[r].v) {
			return find(ns[r].l, key);
		} else {
			return find(ns[r].r, key);
		}
	}
	
	void pr(int r, int ll, int rr) {
		if (rr < ll) return;
		if (ll < 0 || rr < 0) return;
		if (r == -1) {
			return ;
		} else {
			if (ns[r].ln > rr || ns[r].ln < ll) {
				if (ns[r].ln > rr) {
					pr(ns[r].l, ll, rr);
				}
				if (ns[r].ln < ll) {
					pr(ns[r].r, ll-ns[r].ln-1, rr-ns[r].ln-1);
				}
			} else {
				pr(ns[r].l, ll, ns[r].ln);
				cout << ns[r].v << " " ;
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

treap t;

void work() {
	int q, n, tmp;
	scanf("%d", &n);
	t.init();
	for (int i = 0; i < n; i++) {
		scanf("%d", &tmp);
		t.insert(t.root, tmp);
	}
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		scanf("%d", &tmp);
		t.find(t.root, tmp);
		puts("");
	}
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		work();
	}
}

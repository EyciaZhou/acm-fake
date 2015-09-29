//
//  main.cpp
//  Uvalive5817.I-Truchet Tiling
//
//  Created by eycia on 29/9/15.
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

char tmp[200];
int mp[300][300];

double area[90005];
int fa[90005];

const double pi = acos(-1);
const double a1 = pi/4;
const double a2 = 1-a1;

inline int z(int l, int r) {
	return l*300+r;
}

int getf(int f) {
	return fa[f] < 0 ? f : fa[f] = getf(fa[f]);
}

void mer(int l, int r) {
	int f1 = getf(l), f2 = getf(r);
	if (f1 != f2) {
		fa[f1] = f2;
	}
}

void work() {
	int r, c;
	scanf("%d %d", &r, &c);
	
	memset(fa, -1, sizeof(fa));
	
	for (int i = 0; i < 90005; i++) {
		area[i] = 1;
	}
	
	for (int i = 0; i < r; i++) {
		scanf("%s", tmp);
		for (int j = 0; j < c; j++) {
			mp[i][j] = (tmp[j] == '1');
			if (mp[i][j]) {
				mer(z(i*2, j*2), z(i*2+1, j*2+1));
				area[z(i*2, j*2)] += a2;
				area[z(i*2+1, j*2+1)] += a2;
				area[z(i*2, j*2+1)] -= a2;
				area[z(i*2+1, j*2)] -= a2;
			} else {
				mer(z(i*2+1, j*2), z(i*2, j*2+1));
				area[z(i*2, j*2)] -= a2;
				area[z(i*2+1, j*2+1)] -= a2;
				area[z(i*2, j*2+1)] += a2;
				area[z(i*2+1, j*2)] += a2;
			}
		}
	}
	
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (i != r-1) {
				mer(z(i*2+1, j*2), z(i*2+2, j*2));
				mer(z(i*2+1, j*2+1), z(i*2+2, j*2+1));
			}
			
			if (j != c-1) {
				mer(z(i*2, j*2+1), z(i*2, j*2+2));
				mer(z(i*2+1, j*2+1), z(i*2+1, j*2+2));
			}
		}
	}
	/*
	for (int i = 0; i < 2*r; i++) {
		for (int j = 0; j < 2*c; j++) {
			cout << area[z(i, j)] << "	";
		}
		cout << endl;
	}
	*/
	for (int i = 0; i < 2*r; i++) {
		for (int j = 0; j < 2*c; j++) {
			int zz = z(i, j);
			if (getf(zz) != zz) {
				area[getf(zz)] += area[zz];
				area[zz] = 0;
			}
		}
	}
	/*
	cout << endl;
	for (int i = 0; i < 2*r; i++) {
		for (int j = 0; j < 2*c; j++) {
			cout << area[getf(z(i, j))] << "	";
		}
		cout << endl;
	}*/

	
	int q, ll, rr;
	double ans;
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &ll, &rr);
		if (ll%2==1 || rr%2==1) {
			if (ll%2==1 && rr%2==1) {
				//..
				if (mp[ll/2][rr/2]) {
					ans = area[getf(z(ll ,rr))];
				} else {
					ans = area[getf(z(ll-1, rr))];
				}
			} else {
				//oo
				ans = 0;
			}
		} else {
			if (ll != 0) ll--;
			if (rr != 0) rr--;
			ans = area[getf(z(ll, rr))];
			//ans = area[getf(z(ll/4*4+ll/2%2, rr/4*4+rr/2%2))];
			//xx
		}
		printf("%.4lf\n", ans);
	}
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int ff = 1; ff <= t; ff++) {
		printf("Case %d:\n", ff);
		work();
	}
}
/*
3 1
1
0
1
2
3 1
4 2
*/

/*
4 4
0001
0010
1110
0011
*/
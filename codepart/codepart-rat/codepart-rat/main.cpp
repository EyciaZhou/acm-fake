//
//  main.cpp
//  codepart-rat
//
//  Created by eycia on 25/8/15.
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

#define ll long long

ll inline gcd(ll l, ll r) {
	if (l == 0 || r == 0) return max(l, r);
	return __gcd(l, r);
}

struct rat {
	ll up, dw;
	rat(ll u, ll d) : up(u), dw(d) {ll g = gcd(up, dw); if (g==0) g=1; up/=g; dw /= g;}
};

rat inline operator+(const rat &l, const rat &r) {return rat(l.up*r.dw+r.up*l.dw, l.dw * r.dw);}
rat inline operator*(const rat &l, const rat &r) {return rat(l.up*r.up, l.dw*r.dw);}
rat inline operator-(const rat &l, const rat &r) {return rat(l.up*r.dw-r.up*l.dw, l.dw * r.dw);}
rat inline operator/(const rat &l, const rat &r) {return rat(l.up*r.dw, l.dw*r.up);}

rat inline operator+(const rat &l, ll r) {return rat(l.up+r*l.dw, l.dw);}
rat inline operator*(const rat &l, ll r) {return rat(l.up*r, l.dw);}
rat inline operator-(const rat &l, ll r) {return rat(l.up-r*l.dw, l.dw);}
rat inline operator/(const rat &l, ll r) {return rat(l.up, l.dw*r);}

bool inline operator<(const rat &l, const rat &r) {rat tmp = l/r; return tmp.up<tmp.dw;}

int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Hello, World!\n";
    return 0;
}

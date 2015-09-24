//
//  main.cpp
//  Uvalive5714.B-Hou Yi's secret
//
//  Created by eycia on 24/8/15.
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

#define eps 1e-8

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

struct po {
	ll x, y;
	po() : x(0), y(0) {}
	po(ll xx, ll yy) : x(xx), y(yy) {}
};

struct vec {
	ll x, y;
	vec() : x(0), y(0) {}
	vec(ll xx, ll yy) : x(xx), y(yy) {}
	vec(po from, po to) : x(to.x - from.x), y(to.y - from.y){}
	ll lens2() {return x * x + y * y;}
	vec vertical() {return vec(-y, x);} //垂直
	vec unit(); //单位
};

po inline operator+(const po &p, const vec &v) {return po(p.x + v.x, p.y + v.y);}
po inline operator-(const po &p, const vec &v) {return po(p.x - v.x, p.y - v.y);}
vec inline operator-(const po &p1, const po &p2) {return vec(p1.x-p2.x, p1.y-p2.y);}
vec inline operator*(const vec &v, double b) {return vec(v.x * b, v.y * b);}
vec inline operator+(const vec &l, const vec &r) {return vec(l.x+r.x, l.y+r.y);}
ll inline operator*(const vec &v1, const vec &v2) {return v1.x * v2.x + v1.y * v2.y;}
ll inline operator^(const vec &v1, const vec &v2) {return v1.x * v2.y - v2.x * v1.y;}

rat inline f(vec v1, vec v2) {
	return rat((v1*v2)*(v1*v2), v1.lens2()*v2.lens2());
}

vector<po> ps;
vector<pair<int, int> > pps;

struct st {
	double a, b;
	st (double a, double b) : a(a), b(b) {}
};

map<pair<rat, rat >, int> ss;

vector<rat > tmp;

int main(int argc, const char * argv[]) {
	int n, x, y;
	while (scanf("%d", &n), n) {
		ps.clear();
		pps.clear();
		ss.clear();
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			pps.push_back(make_pair(x, y));
		}
		
		sort(pps.begin(), pps.end());
		pps.erase(unique(pps.begin(), pps.end()), pps.end());
		
		n = pps.size();
		
		for (int i = 0; i < n; i++) {
			ps.push_back(po(pps[i].first, pps[i].second));
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				vec v1 = vec(ps[i], ps[j]);
				if (v1.lens2() < eps) continue;
				for (int k = j+1; k < n; k++) {
					tmp.clear();
					vec v2 = vec(ps[i], ps[k]);
					vec v3 = vec(ps[j], ps[k]);
					if (v2.lens2() < eps || v3.lens2() < eps) continue;
					if (fabs(v2 ^ v3) < eps || fabs(v1 ^ v2) < eps || fabs(v1 ^ v3) < eps) continue;
		
					rat ang1 = f(v1, v2), ang2 = f(v2, v3), ang3 = f(vec(ps[j], ps[i]), vec(ps[j], ps[k]));
					tmp.push_back(ang1);
					tmp.push_back(ang2);
					tmp.push_back(ang3);
					
					sort(tmp.begin(), tmp.end());
					
					ss[make_pair(tmp[0], tmp[1])]++;
				}
			}
		}
		int mx = 0;
		for (map<pair<rat, rat >, int>::iterator it = ss.begin(); it != ss.end(); it++) {
			if (it->second > mx) {
				mx = it->second;
			}
		}
		printf("%d\n", mx);
	}
}

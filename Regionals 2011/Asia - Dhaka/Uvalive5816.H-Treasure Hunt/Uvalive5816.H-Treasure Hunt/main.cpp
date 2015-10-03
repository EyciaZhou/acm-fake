//
//  main.cpp
//  Uvalive5816.H-Treasure Hunt
//
//  Created by eycia on 3/10/15.
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

//const part
double pi = acos(-1.0);
double eps = 1e-9;
double deg2ang = 180/pi;
double ang2deg = pi/180;

struct po {
	double x, y;
	po() : x(0), y(0) {}
	po(double xx, double yy) : x(xx), y(yy) {}
};

struct vec {
	double x, y;
	vec() : x(0), y(0) {}
	vec(double xx, double yy) : x(xx), y(yy) {}
	vec(po from, po to) : x(to.x - from.x), y(to.y - from.y){}
	double lens() {return sqrt(x * x + y * y);}
	vec vertical() {return vec(-y, x);} //垂直
	vec unit(); //单位
};

//operator of base part
po inline operator+(const po &p, const vec &v) {return po(p.x + v.x, p.y + v.y);}
po inline operator-(const po &p, const vec &v) {return po(p.x - v.x, p.y - v.y);}
vec inline operator-(const po &p1, const po &p2) {return vec(p1.x-p2.x, p1.y-p2.y);}
vec inline operator*(const vec &v, double b) {return vec(v.x * b, v.y * b);}
vec inline operator+(const vec &l, const vec &r) {return vec(l.x+r.x, l.y+r.y);}
double inline operator*(const vec &v1, const vec &v2) {return v1.x * v2.x + v1.y * v2.y;}
double inline operator^(const vec &v1, const vec &v2) {return v1.x * v2.y - v2.x * v1.y;}
int neg(double n) {if (n > eps) return 1; else if (n < -eps) return -1; else return 0;}

vec inline vec::unit() {return *this * (1/lens());}

po intersection(po u1,po u2,po v1,po v2){//求交 共线nan
	double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))/((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
	po ret=u1;ret.x+=(u2.x-u1.x)*t;ret.y+=(u2.y-u1.y)*t;return ret;}

bool is_cross(po u1, po u2, po v1, po v2) { // 判交 = 0可以相交于端点
	double tmp1 = (v1-u1) ^ (u2-u1), tmp2 = (u2-u1) ^ (v2-u1), tmp3 = (u1-v1) ^ (v2-v1), tmp4 = (v2-v1) ^ (u2-v1);
	if(neg(tmp1*tmp2) >= 0 && neg(tmp3*tmp4) >= 0) return true;
	return false;}

po pos[4];

bool inside(double px, double py) {
	bool b = true;
	
	for (int i = 0; i < 4; i++) {
		vec v1 = vec(po(px, py), po(pos[i].x, pos[i].y));
		vec v2 = vec(po(px, py), po(pos[(i+1)%4].x, pos[(i+1)%4].y));
		
		cout << (v1 ^ v2) << endl;
		
		b &= (v1 ^ v2) < 0;
	}
	
	return b;
}

int main(int argc, const char * argv[]) {
	po p[4];
	while (true) {
		double tx = 0, ty = 0;
		
		for (int i = 0; i < 4; i++) {
			scanf("%lf %lf", &p[i].x, &p[i].y);
			tx += p[i].x;
			ty += p[i].y;
		}
		
		double cx = 0, cy = 0;
		
		for (int i = 0; i < 4; i++) {
			scanf("%lf", &pos[i].x);
			scanf("%lf", &pos[i].y);
			cx += pos[i].x;
			cy += pos[i].y;
		}
		
		bool fl = true;
		
		for (int i = 0; i < 4; i++) {
			if (p[i].x != 0 || p[i].y != 0 || pos[i].x != 0 || pos[i].y != 0) {
				fl = false;
			}
		}
		
		if (fl) break;
		
		vec tar = vec(po(tx, ty), po(cx, cy));
		vec nn = tar.unit();
		
		for (int i = 0; i < 4; i++) {
			bool meet = false;
			double len = tar.lens();
			for (int j = 0; j < 4; j++) {
				if (is_cross(p[i], p[i]+tar, pos[j], pos[(j+1)%4])) {
					po me = intersection(p[i], p[i]+tar, pos[j], pos[(j+1)%4]);
					if (!meet) {
						len = vec(me, p[i]).lens();
					} else {
						len = min(len, vec(me, p[i]).lens());
					}
					meet = true;
				}
			}
			
			p[i] = p[i] + nn * len;
			
			tar = tar + nn * (-len);
			
			if (!meet) break;
		}
		
		for (int i = 0; i < 4; i++) {
			printf("%.12lf %.12lf\n", p[i].x, p[i].y);
		}
	}
}

//
//  main.cpp
//  Sojos2.b
//
//  Created by eycia on 5/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

#define eps 1e-8

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

po inline operator+(const po &p, const vec &v) {return po(p.x + v.x, p.y + v.y);}
po inline operator-(const po &p, const vec &v) {return po(p.x - v.x, p.y - v.y);}
vec inline operator-(const po &p1, const po &p2) {return vec(p1.x-p2.x, p1.y-p2.y);}
vec inline operator*(const vec &v, double b) {return vec(v.x * b, v.y * b);}
vec inline operator+(const vec &l, const vec &r) {return vec(l.x+r.x, l.y+r.y);}
double inline operator*(const vec &v1, const vec &v2) {return v1.x * v2.x + v1.y * v2.y;}
double inline operator^(const vec &v1, const vec &v2) {return v1.x * v2.y - v2.x * v1.y;}
vec vec::unit() {return *this * (1/lens());}

int main(int argc, const char * argv[]) {
	double step;
	po now;
	po to;
	int ff = 0;
	while (cin >> step >> now.x >> now.y) {
		ff++;
		if (step == 0) break;
		bool ct = false;
		while (true) {
			cin >> to.x >> to.y;
			if (to.x == -1 && to.y == -1) break;
			if (!ct) {
				vec v(now, to);
				
				now = now + v.unit() * min(step, v.lens());
				if (vec(now, to).lens() <= 1) {
					ct = true;
					now.x = to.x;
					now.y = to.y;
				}
			}
		}
		if (ct) {
			printf("Firefly %d caught at (%.0lf,%.0lf)\n", ff, now.x, now.y);
		} else {
			printf("Firefly %d not caught\n", ff);
		}
	}
}

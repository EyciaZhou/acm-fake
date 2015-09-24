//
//  main.cpp
//  fake4.g
//
//  Created by eycia on 31/7/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

double pi = acos(-1.0);
double eps = 1e-9;

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

inline double to2pi(double a) {while (a < 0) a+=2*pi;while (a >= 2*pi) a-=2*pi;return a;}

int main(int argc, const char * argv[]) {
	int t, n;
	po p1, p2;
	po o(0, 0);
	po y0(1, 0);
	scanf("%d", &t);
	while (t--) {
		double tot = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %lf %lf", &p1.x, &p1.y, &p2.x, &p2.y);
			double ang1 = atan2(p1.x, p1.y);
			double ang2 = atan2(p2.x, p2.y);
			double ang = to2pi(ang1 - ang2);
			//cout << ang1 << " " << ang2 << " " << ang << " ";
			if (ang > pi) {
				ang = 2*pi - ang;
			}
			//cout << ang << endl;
			tot += ang;
		}
		printf("%.5lf\n", tot/2/pi);
	}
}

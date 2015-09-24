//
//  main.cpp
//  Uvalive5719.G-A Letter to Programmers
//
//  Created by eycia on 6/9/15.
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

#define rep(i,t) for(int (i)=0;(i)<(t);(i)++)

//const part
double pi = acos(-1.0);
double eps = 1e-2;
double deg2ang = 180/pi;
double ang2deg = pi/180;

//base type part
struct po3 {
	double x, y, z;
	po3() : x(0), y(0), z(0) {}
	po3(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}
};

struct vec3 {
	double x, y, z;
	vec3() : x(0), y(0), z(0) {}
	vec3(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}
	vec3(po3 from, po3 to) : x(to.x - from.x), y(to.y - from.y), z(to.z - from.z){}
	double lens() {return sqrt(x * x + y * y + z*z);}
	vec3 vertical() {return vec3(-y, x, z);} //垂直
	vec3 unit(); //单位
};


struct mat4x4 {
	double a, b, c, d;
	double e, f, g, h;
	double i, j, k, l;
	double m, n, o, p;
	inline double& operator[](size_t idx) {return ((double *)this)[idx];};
	inline const double& operator[](size_t idx) const {return ((double *)this)[idx];};
#define dd double
	mat4x4(dd a, dd b, dd c, dd d, dd e, dd f, dd g, dd h, dd i, dd j, dd k, dd l, dd m, dd n, dd o, dd p) :
		a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p) {}
	mat4x4() {for (int i = 0; i < 16; i++) this->operator[](i) = 0.0;}
#undef dd
	void pr(){rep(i, 4) {rep(j, 4) cout << this->operator[](i*4+j) << " "; cout << endl;}cout << endl;}
	void fix(){
		rep(i,16) if (fabs((*this)[i]) < eps) (*this)[i] = 0;
	}
};

//operator of base part
po3 inline operator+(const po3 &p, const vec3 &v) {return po3(p.x + v.x, p.y + v.y, p.z + v.z);}
po3 inline operator-(const po3 &p, const vec3 &v) {return po3(p.x - v.x, p.y - v.y, p.z - v.z);}
vec3 inline operator-(const po3 &p1, const po3 &p2) {return vec3(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z);}
vec3 inline operator*(const vec3 &v, double b) {return vec3(v.x * b, v.y * b, v.z * b);}
vec3 inline operator+(const vec3 &l, const vec3 &r) {return vec3(l.x+r.x, l.y+r.y, l.z+r.z);}
double inline operator*(const vec3 &v1, const vec3 &v2) {return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;}
double inline operator^(const vec3 &v1, const vec3 &v2) {return (v1.y*v2.z - v1.z*v2.y) + (v1.z*v2.x-v1.x*v2.z) + (v1.x*v2.y-v1.y*v2.x);}
//(Yu*Zv – Zu*Yv)*i + (Zu*Xv – Xu*Zv)j + (Xu*Yv – Yu*Xv)k;

mat4x4 inline operator*(const mat4x4 &l, const mat4x4 &r) {
	mat4x4 tmp;rep(i, 4) rep(j, 4) rep(k, 4) tmp[i*4+j] += l[i*4+k]*r[k*4+j];return tmp;}
po3 inline operator*(const po3 &p, const mat4x4 &m) {
	double mat[4] = {p.x, p.y, p.z, 1}; double res[4] = {0.0, 0.0, 0.0, 0.0};
	rep(i, 4) {
		rep(j, 4) {
			res[i] += m[j*4+i]*mat[j];
		}
		if (fabs(res[i]) < eps) res[i] = 0; //not include the temp
	}
	return po3(res[0], res[1], res[2]);
}



vec3 vec3::unit() {return *this * (1/lens());}

//transform part
#define move3(tx, ty, tz) mat4x4(1,0,0,0, 0,1,0,0, 0,0,1,0, (tx),(ty),(tz),1)
#define scale3(sx,sy,sz) mat4x4((sx),0,0,0, 0,(sy),0,0, 0,0,(sz),0, 0,0,0,1)
inline mat4x4 rotaCounterClockwise3(double theta, vec3 v) {
	double s = sin(theta), c = cos(theta), c1 = 1-c, x = v.x, y = v.y, z = v.z;
	v = v.unit();
	return mat4x4(
		c+c1*x*x, c1*x*y-s*z, c1*x*z+s*y, 0,
		c1*y*x+s*z, c+c1*y*y, c1*y*z-s*x, 0,
		c1*z*x-s*y, c1*z*y+s*x, c+c1*z*z, 0,
		0, 0, 0, 1);
}
#define rotaClockwise3(theta, v) rotaCounterClockwise3(-theta, v)
#define rota3(theta, v) rotaClockwise3(theta, v)
#define one      mat4x4 (1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1)

char o[20];

mat4x4 ksm(mat4x4 n, int up) {
	mat4x4 res = one;
	mat4x4 tmp = n;
	while (up) {
		if (up&1) {
			res = res * tmp;
		}
		tmp = tmp * tmp;
		up >>= 1;
	}
	return res;
}

mat4x4 rd() {
	mat4x4 mat = one;
	double x, y, z, d;
	int r;
	while (true) {
		scanf("%s", o);
		if (o[0] == 't') {
			scanf("%lf %lf %lf", &x, &y, &z);
			mat = mat*move3(x, y, z);
		}
		if (o[0] == 's') {
			scanf("%lf %lf %lf", &x, &y, &z);
			mat = mat*scale3(x, y, z);
		}
		if (o[0] == 'r' && o[1] == 'o') {
			scanf("%lf %lf %lf %lf", &x, &y, &z, &d);
			mat = mat*rota3(d*ang2deg, vec3(po3(0, 0, 0), po3(x, y, z)).unit());
		}
		if (o[0] == 'e') {
			return mat;
		}
		if (o[0] == 'r' && o[1] == 'e') {
			scanf("%d", &r);
			mat4x4 n = rd();
			mat = mat * ksm(n, r);
		}
	}
	return one;
}

int main(int argc, const char * argv[]) {
	int n;
	double x, y, z;
	while (scanf("%d", &n) != EOF) {
		if (n == 0) break;
		mat4x4 mat = rd();
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %lf", &x, &y, &z);
			po3 ans = po3(x, y, z)*mat;
			printf("%.2lf %.2lf %.2lf\n", ans.x, ans.y, ans.z);
		}
		puts("");
	}
}

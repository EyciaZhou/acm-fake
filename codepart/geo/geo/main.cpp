//
//  main.cpp
//  geo
//
//  Created by eycia on 9/9/15.
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
double eps = 1e-9;
double deg2ang = 180/pi;
double ang2deg = pi/180;

//base type part
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

struct cir {
	po o;
	double r;
	cir(po o, double r) : o(o), r(r) {}
	bool insi(po &p);   //judge if p inside the cir
	void meet(po &p1, po &p2, po &r1, po &r2); //meet the line on p1, p2 returns r1 r2
	int meet_seg(po &p1, po &p2, po &r1, po &r2); //meet the seg of p1, p2 returns r1 r2 and which
	int meet_cir(cir c, po &r1, po &r2);
	double two_po_ang(po &p1, po &p2);
};


struct mat3x3 {
	double a, b, c;
	double d, e, f;
	double g, h, i;
	inline double& operator[](size_t idx) {return ((double *)this)[idx];};
	inline const double& operator[](size_t idx) const {return ((double *)this)[idx];};
#define dd double
	mat3x3(dd a, dd b, dd c, dd d, dd e, dd f, dd g, dd h, dd i) : a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i) {}
	mat3x3() {for (int i = 0; i < 9; i++) this->operator[](i) = 0.0;}
#undef dd
	void pr(){rep(i, 3) {rep(j, 3) cout << this->operator[](i*3+j) << " "; cout << endl;}cout << endl;}
	void fix(){
		rep(i,9) if (fabs((*this)[i]) < eps) (*this)[i] = 0;
	}
};

//angle part
double inline cos_low(double a, double b, double c) { return (b*b+c*c-a*a)/(2*b*c); }

//operator of base part
po inline operator+(const po &p, const vec &v) {return po(p.x + v.x, p.y + v.y);}
po inline operator-(const po &p, const vec &v) {return po(p.x - v.x, p.y - v.y);}
vec inline operator-(const po &p1, const po &p2) {return vec(p1.x-p2.x, p1.y-p2.y);}
vec inline operator*(const vec &v, double b) {return vec(v.x * b, v.y * b);}
vec inline operator+(const vec &l, const vec &r) {return vec(l.x+r.x, l.y+r.y);}
double inline operator*(const vec &v1, const vec &v2) {return v1.x * v2.x + v1.y * v2.y;}
double inline operator^(const vec &v1, const vec &v2) {return v1.x * v2.y - v2.x * v1.y;}

mat3x3 inline operator*(const mat3x3 &l, const mat3x3 &r) {
	mat3x3 tmp;rep(i, 3) rep(j, 3) rep(k, 3) tmp[i*3+j] += l[i*3+k]*r[k*3+j];return tmp;}
po inline operator*(const po &p, const mat3x3 &m) //{double t1=0, t2=0;rep(i, 3) {t1+=p.x*m[i*3];t2+=p.y*m[i*3+1];}return po(t1, t2);}
{
	double mat[3] = {p.x, p.y, 1}; double res[3] = {0.0, 0.0, 0.0};
	rep(i, 3) {
		rep(j, 3) {
			res[j] += mat[i*3+j];
		}
	}
	return po(res[0], res[1]);
}

//etc part
double inline distant(po p1, po p2) {return vec(p1, p2).lens();}
double inline distant(po p, po v1, po v2) {if (fabs(vec(v1, v2).lens()) < eps) return distant(p, v1); return fabs(vec(p, v1) * vec(v1, v2).vertical().unit());}
double vec2deg(vec v1, vec v2) {return acos(max(min(v1 * v2 / v1.lens() / v2.lens(), 1.0), -1.0));} //return the deg of two vector
int neg(double n) {if (n > eps) return 1; else if (n < -eps) return -1; else return 0;}
double inline safe(double a) {return (a != a) ? 0 : a;}
double inline to2pi(double a) {while (a < 0) a+=2*pi;while (a >= 2*pi) a-=2*pi;return a;}
double inline topi(double a) {double b = to2pi(a); if (b > pi) b = 2*pi - b; return b;}
double inline area(vec v1, vec v2) {return fabs((v1 ^ v2) * 0.5);}

po intersection(po u1,po u2,po v1,po v2){//求交 共线nan
	double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))/((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
	po ret=u1;ret.x+=(u2.x-u1.x)*t;ret.y+=(u2.y-u1.y)*t;return ret;}

bool is_cross(po u1, po u2, po v1, po v2) { // 判交 = 0可以相交于端点
	double tmp1 = (v1-u1) ^ (u2-u1), tmp2 = (u2-u1) ^ (v2-u1), tmp3 = (u1-v1) ^ (v2-v1), tmp4 = (v2-v1) ^ (u2-v1);
	if(neg(tmp1*tmp2) >= 0 && neg(tmp3*tmp4) >= 0) return true;
	return false;}

//this part shound with base type part
vec inline vec::unit() {return *this * (1/lens());}
bool inline cir::insi(po &p) {return (distant(o, p) < r);}
void cir::meet(po &p1, po &p2, po &r1, po &r2) {
	vec a = vec(p1, p2).vertical().unit() * distant(o, p1, p2);
	a = a * neg(a * vec(o, p1));
	vec b = vec(p1, p2).unit() * sqrt(max(r * r - a * a, 0.0));
	r1=o+a-b;
	r2=o+a+b;
}//r1左侧（p1侧）

//return 00 01 10 11
int cir::meet_seg(po &p1, po &p2, po &r1, po &r2) {
	if (this->insi(p1) && this->insi(p2)) return 0;
	this->meet(p1, p2, r1, r2);
	if (this->insi(p1)) return 2;
	if (this->insi(p2)) return 1;
	if (distant(o, p1, p2) < r) {
		if (neg(vec(o, p1) * vec(p1, p2)) == neg(vec(o, p2) * vec(p1, p2))) return 0;
		return 3;
	}
	return 0;
}

// 0:外离 1:内含 2:外切 3:内切 4:相交
int meet_cir_stat(double d, double k, double r) {
	if (r > k) swap(k, r);
	if (fabs(d-r-k) < eps) return 2;
	if (fabs(d+r-k) < eps) return 3;
	if (d > r+k) return 0;
	if (d < r-k) return 1;
	return 4;
}

//return meet number
int cir::meet_cir(cir c, po &re1, po &re2) {
	vec toward(o, c.o);
	double d = toward.lens(), r1 = r, r2 = c.r;
	int stat = meet_cir_stat(d, r1, r2);
	//cout << stat << endl;
	if (stat <= 1) {
		return 0;
	}
	if (stat <= 3) {
		if (r1 < r2 && stat == 3) {
			re1 = o-toward.unit()*r1;
		} else {
			re1 = o+toward.unit()*r1;
		}
		return 1;
	}
	double costheta = cos_low(r2, r1, d);
	double d1 = costheta * r1;
	double x = sqrt(r1*r1-d1*d1);
	vec v = toward.unit()*d1;
	vec b = toward.vertical().unit()*x;
	re1 = o+v+b;
	re2 = o+v-b;
	return 2;
}

double cir::two_po_ang(po &p1, po &p2) {
	double ang1 = atan2((p1 - this->o).x, (p1 - this->o).y);
	double ang2 = atan2((p2 - this->o).x, (p2 - this->o).y);
	return topi(ang1 - ang2);
}

//transform part
#define move(tx, ty) mat3x3(1, 0, 0, 0, 1, 0, (tx), (ty), 1)
#define scale(sx,sy) mat3x3((sx), 0, 0, 0, (sy), 0, 0, 0, 1)
#define rotaCounterClockwise(theta) mat3x3(cos(theta), sin(theta), 0, -sin(theta), cos(theta), 0, 0, 0, 1)
#define rotaClockwise(theta) rotaCounterClockwise(-theta)
#define rota(theta) rotaCounterClockwise(theta)
#define withPo(expr, po) move(-po.x, -po.y)*(expr)*move(po.x, po.y)
#define rotaWithPo(theta, po) withPo(rota(theta), po)
#define scaleWithPo(sx, sy, po) withPo(scale(sx, sy), po)
#define symABx   mat3x3 ( 1,0,0, 0,-1,0,0,0,1)
#define symABy   mat3x3 (-1,0,0, 0, 1,0,0,0,1)
#define symABo   mat3x3 (-1,0,0, 0,-1,0,0,0,1)
#define symABxy  mat3x3 (0, 1,0, 1, 0,0,0,0,1)
#define symABxfy mat3x3 (0,-1,0,-1, 0,0,0,0,1)
#define one3      mat3x3 (1, 0,0, 0, 1,0,0,0,1)


#define mr1 mat[0]
#define mr2 mat[1]
#define mr3 mat[3]
#define mr4 mat[4]
#define ma1 mat[6]
#define ma2 mat[7]

//矩阵反演 当矩阵只经过旋转平移时
#define re_theta atan2(mr2,mr1)
#define re_mx (-mr2*ma2-ma1*(mr1-1))/((mr1-1)*(mr1-1)+mr2*mr2)
#define re_my ( mr2*ma1-ma2*(mr1-1))/((mr1-1)*(mr1-1)+mr2*mr2)

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
	double s = sin(theta), c = cos(theta), c1 = 1-c, x = v.x, y = v.y, z = v.z;v = v.unit();
	return mat4x4(
				  c+c1*x*x, c1*x*y-s*z, c1*x*z+s*y, 0,
				  c1*y*x+s*z, c+c1*y*y, c1*y*z-s*x, 0,
				  c1*z*x-s*y, c1*z*y+s*x, c+c1*z*z, 0,
				  0, 0, 0, 1);
}
#define rotaClockwise3(theta, v) rotaCounterClockwise3(-theta, v)
#define rota3(theta, v) rotaClockwise3(theta, v)
#define one4      mat4x4 (1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1)

int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Hello, World!\n";
    return 0;
}

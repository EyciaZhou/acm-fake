//
//  main.cpp
//  Hdu4766.H-Network
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
	cir() {}
	bool insi(po &p);   //judge if p inside the cir
	bool insi_eq(po &p);   //judge if p inside the cir
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
bool inline cir::insi_eq(po &p) {return (distant(o, p) <= r+eps);}
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

//tubao
#define point po
bool mult(point sp, point ep, point op){
	return (sp.x - op.x) * (ep.y - op.y) >= (ep.x - op.x) * (sp.y - op.y);
}

bool operator < (const point &l, const point &r){
	return l.y < r.y || (l.y == r.y && l.x < r.x);
}

int graham(point pnt[], int n, point res[]){
	int i, len, top = 1;
	sort(pnt, pnt + n);
	if (n == 0) return 0; res[0] = pnt[0];
	if (n == 1) return 1; res[1] = pnt[1];
	if (n == 2) return 2; res[2] = pnt[2];
	for (i = 2; i < n; i++) {
		while (top && mult(pnt[i], res[top], res[top-1])) top--;
		res[++top] = pnt[i];
	}
	len = top; res[++top] = pnt[n - 2];
	for (i = n - 3; i >= 0; i--) {
		while (top!=len && mult(pnt[i], res[top],
								res[top-1])) top--;
		res[++top] = pnt[i];
	}
	return top;
}
#undef point

po ps[1005], rps[1005];

int n;

bool all_inside(cir c) {
	bool fd = true;
	for (int i = 0; i < n; i++) {
		if (!c.insi_eq(rps[i])) {
			fd = false;
			break;
		}
	}
	return fd;
}

po m;

bool cmp(const po &le, const po &ri) {
	return distant(m, le) > distant(m, ri);
}

int main(int argc, const char * argv[]) {
	double d;
	//freopen("/Users/eycia/i", "r", stdin);
	while (scanf("%lf %lf %lf", &m.x, &m.y, &d) != EOF) {
		scanf("%d", &n);
		
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &ps[i].x, &ps[i].y);
		}
		n = graham(ps, n, rps);
		
		bool finded = false;
		double di = 0;
		
		if (all_inside(cir(m, d))) {
			puts("0.00");
			continue;
		}
		
		sort(rps, rps+n, cmp);
		
		for (int i = 0; i < n; i++) {
			vec v1(rps[i], m);
			v1 = v1.unit();
			
			po p2 = rps[i] + v1 * d;
			
			if (all_inside(cir(p2, d))) {
				double dis = distant(p2, m);
				if (!finded || dis < di) {
					di = dis;
					finded = true;
				}
			}
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				vec v1(rps[i], rps[j]);
				double d1 = v1.lens() * 0.5;
				double d2 = sqrt(d*d-d1*d1);
				vec v2 = v1.vertical().unit();
				
				cir c[2];
				
				c[0] = cir(rps[i] + v1*0.5 + v2*d2, d);
				c[1] = cir(rps[i] + v1*0.5 - v2*d2, d);
				
				for (int oo = 0; oo < 2; oo++) {
					double dis = distant(c[oo].o, m);
					if (finded && dis > di) {
						continue;
					}
					
					if (all_inside(c[oo])) {
						if (!finded || dis < di) {
							di = dis;
							finded = true;
						}
					}
				}
			}
		}
		if (!finded) {
			puts("X");
		} else {
			printf("%.2lf\n", di);
		}
	}
}

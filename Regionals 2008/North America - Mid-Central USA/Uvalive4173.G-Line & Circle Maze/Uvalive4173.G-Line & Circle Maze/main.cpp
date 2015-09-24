//
//  main.cpp
//  Sosjo2.g
//
//  Created by eycia on 5/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//const part
double pi = acos(-1.0);
double eps = 1e-9;
double deg2ang = 360/pi;
double ang2deg = pi/360;

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

char op[5];

vector<pair<po, po> > ls;
vector<cir> cs;

vector<unsigned long> pls[50];
vector<unsigned long> pcs[50];

vector<po> ps;

double mp[405][405];

int main(int argc, const char * argv[]) {
	double a, b, c, d;
	int ff = 0;
	while (true) {
		ff++;
		scanf("%s", op);
		if (op[0] == '*') break;
		ls.clear();
		cs.clear();
		ps.clear();
		for (int i = 0; i < 50; i++) {
			pls[i].clear();pcs[i].clear();
		}
		while (true) {
			if (op[0] == '*') break;
			if (op[0] == 'L') {
				scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
				ls.push_back({po(a, b), po(c, d)});
			} else {
				scanf("%lf %lf %lf", &a, &b, &c);
				cs.push_back(cir(po(a, b), c));
			}
			scanf("%s", op);
		}
		
		//seg's two po
		for (int i = 0; i < ls.size(); i++) {
			ps.push_back(ls[i].first);
			pls[i].push_back(ps.size()-1);
			ps.push_back(ls[i].second);
			pls[i].push_back(ps.size()-1);
		}
		
		//circle meet with segment
		po r1, r2;
		for (int i = 0; i < cs.size(); i++) {
			for (int j = 0; j < ls.size(); j++) {
				int ans = cs[i].meet_seg(ls[j].first, ls[j].second, r1, r2);
				switch (ans) {
					case 1:
						ps.push_back(r1);
						pcs[i].push_back(ps.size()-1);
						pls[j].push_back(ps.size()-1);
						break;
					case 2:
						ps.push_back(r2);
						pcs[i].push_back(ps.size()-1);
						pls[j].push_back(ps.size()-1);
						break;
					case 3:
						ps.push_back(r1);
						pcs[i].push_back(ps.size()-1);
						pls[j].push_back(ps.size()-1);
						ps.push_back(r2);
						pcs[i].push_back(ps.size()-1);
						pls[j].push_back(ps.size()-1);
						break;
				}
			}
		}
		
		//segment meet with segment
		for (int i = 0; i < ls.size(); i++) {
			for (int j = i+1; j < ls.size(); j++) {
				if (is_cross(ls[i].first, ls[i].second, ls[j].first, ls[j].second)) {
					r1 = intersection(ls[i].first, ls[i].second, ls[j].first, ls[j].second);
					ps.push_back(r1);
					pls[i].push_back(ps.size()-1);
					pls[j].push_back(ps.size()-1);
				}
			}
		}
		
		//circle meet with circle
		for (int i = 0; i < cs.size(); i++) {
			for (int j = i+1; j < cs.size(); j++) {
				int ans = cs[i].meet_cir(cs[j], r1, r2);
				if (ans == 1) {
					ps.push_back(r1);
					pcs[i].push_back(ps.size()-1);
					pcs[j].push_back(ps.size()-1);
				} else if (ans == 2) {
					ps.push_back(r1);
					pcs[i].push_back(ps.size()-1);
					pcs[j].push_back(ps.size()-1);
					ps.push_back(r2);
					pcs[i].push_back(ps.size()-1);
					pcs[j].push_back(ps.size()-1);
				}
			}
		}
		int n = ps.size();
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					mp[i][j] = 0;
				} else {
					mp[i][j] = -1;
				}
			}
		}
		
		for (int i = 0; i < ls.size(); i++) {
			for (int j = 0; j < pls[i].size(); j++) {
				for (int k = j+1; k < pls[i].size(); k++) {
					mp[pls[i][j]][pls[i][k]] = distant(ps[pls[i][j]], ps[pls[i][k]]);
					mp[pls[i][k]][pls[i][j]] = distant(ps[pls[i][j]], ps[pls[i][k]]);
				}
			}
		}
		
		for (int i = 0; i < cs.size(); i++) {
			for (int j = 0; j < pcs[i].size(); j++) {
				for (int k = j+1; k < pcs[i].size(); k++) {
					double ang = cs[i].two_po_ang(ps[pcs[i][j]], ps[pcs[i][k]]);
					mp[pcs[i][j]][pcs[i][k]] = cs[i].r * ang;
					mp[pcs[i][k]][pcs[i][j]] = cs[i].r * ang;
				}
			}
		}
		
		//floyd
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if ((mp[i][k] >= 0 && mp[k][j] >= 0) && (mp[i][j] < 0 || mp[i][k] + mp[k][j] < mp[i][j])) {
						mp[i][j] = mp[i][k] + mp[k][j];
					}
				}
			}
		}
		
		double mx = 0;
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (mp[i][j] > mx) {
					mx = mp[i][j];
				}
			}
		}
		
		printf("Case %d: %.1lf\n", ff, mx);
	}
}
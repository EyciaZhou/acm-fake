//
//  main.cpp
//  fake3.a
//
//  Created by eycia on 30/7/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

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

double inline area(vec v1, vec v2) {return (v1 ^ v2) * 0.5;}

po p[50005];
double ss[50005];

int main(int argc, const char * argv[]) {
    int n, q, a, b;
    scanf("%d %d", &n, &q);
    po o(0, 0);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &p[i].x, &p[i].y);
    }
    ss[0] = 0;
    for (int i = 1; i < n; i++) {
        ss[i] = ss[i-1] + area(vec(o, p[i]), vec(o, p[i-1]));
    }
    double alls = ss[n-1] + area(vec(o, p[0]), vec(o, p[n-1]));
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &a, &b);
        double s1 = ss[b] - ss[a] + area(vec(o, p[a]), vec(o, p[b]));
        double s2 = alls - s1;
        printf("%.1lf\n", min(s1, s2));
    }
}
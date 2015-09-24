//
//  main.cpp
//  cf.320.1.a
//
//  Created by eycia on 16/9/15.
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

#define eps 1e-9

//base type part
struct po {
	double x, y;
	po() : x(0), y(0) {}
	po(double xx, double yy) : x(xx), y(yy) {}
};


po intersection(po u1,po u2,po v1,po v2){//求交 共线nan
	double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))/((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
	po ret=u1;ret.x+=(u2.x-u1.x)*t;ret.y+=(u2.y-u1.y)*t;return ret;}

long long onseg(double a) {
	long long k = (long long)a;
	if (fabs(k-a) < eps) {
		if (k%2==0) {
			k--;
		}
		return k;
	}
	if (k%2==0) k--;
	return k;
}

int main(int argc, const char * argv[]) {
	double a, b;
	cin >> a >> b;
	
	if (b/a > 1) {
		puts("-1");
		return 0;
	}
	
	long long k = onseg(a/b);
	po p = intersection(po(0, 0), po(a, b), po(k, 1), po(k+1, 0));
	printf("%.20lf\n", b/p.y);
}

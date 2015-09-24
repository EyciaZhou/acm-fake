//
//  main.cpp
//  Uvalive4486.D-Download Manager
//
//  Created by eycia on 11/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef pair<double, int> pp;

priority_queue<pp, vector<pp>, greater<pp> > p;
vector<double > p2;

#define eps 1e-8

int main(int argc, const char * argv[]) {
    int t, n, pr, ff = 0;
    double s, b;
    while (scanf("%d %d %lf", &t, &n, &b) != EOF) {
        ff++;
        if (t+n+b == 0) break;
        while (!p.empty()) p.pop();
        for (int i = 0; i < t; i++) {
            scanf("%lf %d", &s, &pr);
            p.push({s, 100-pr});
        }
        for (int i = 0; i < n && !p.empty(); i++) {
            pp tmp = p.top();
            p2.push_back(tmp.first*(tmp.second/100.0));
            p.pop();
        }
        sort(p2.begin(), p2.end());
        double tot = 0;
        
        while (!p2.empty()) {
            double k = p2[0];
            double eachv = b/p2.size();
            
            double bites = k;
            double ti = bites / eachv;
            tot += ti;
            vector<double > t2;
            int succ = 0;
            for (int i = 0; i < p2.size(); i++) {
                p2[i] -= k;
                if (p2[i] < eps) {
                    succ++;
                } else {
                    t2.push_back(p2[i]);
                }
            }
            for (int i = 0; i < succ && !p.empty(); i++) {
                pp tmp = p.top();
                t2.push_back(tmp.first*(tmp.second/100.0));
                p.pop();
            }
            p2.clear();
            for (int i = 0; i < t2.size(); i++) {
                p2.push_back(t2[i]);
            }
            sort(p2.begin(), p2.end());
        }
        printf("Case %d: %.2lf\n\n", ff, tot);
    }
}

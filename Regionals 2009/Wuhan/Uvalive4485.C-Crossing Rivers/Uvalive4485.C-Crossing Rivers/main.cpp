//
//  main.cpp
//  Uvalive4485.C-Crossing Rivers
//
//  Created by eycia on 11/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int n, d, p, ff = 0;
    double l, v;
    while (cin >> n >> d) {
        if (n == 0 && d == 0) break;
        ff++;
        double tot = 0;
        for (int i = 0; i < n; i++) {
            cin >> p >> l >> v;
            d -= l;
            tot += l * 2 / v;
        }
        printf("Case %d: %.3lf\n\n", ff, tot+d);
    }
}

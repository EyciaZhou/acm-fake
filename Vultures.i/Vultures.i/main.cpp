//
//  main.cpp
//  Vultures.i
//
//  Created by eycia on 7/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

char tmp[200];

bool mp[205][205];

int inline z(int x, int y, int xx, int yy) {
    return (x*2+xx) * 105 + (y*2+yy);
}

const double pi = acos(-1);

const double a0 = pi/4;
const double a1 = 4-pi/2;

int fa[41000];
double area[41000];

inline int getf(int s) {
    if (fa[s] == s) {
        return s;
    }
    int k = getf(fa[s]);
    fa[s] = k;
    return k;
}

inline void uni(int s, int t) {
    //cout << s << " " << t << endl;
    int ss = getf(s);
    int tt = getf(t);
    
    if (ss != tt) {
        area[ss] += area[tt];
        area[tt] = 0;
        fa[tt] = fa[ss];
    }
}

int main(int argc, const char * argv[]) {
    int t, n, m;
    cin >> t;
    for (int ff = 1; ff <= t; ff++) {
        for (int i = 0; i < 41000; i++) {
            fa[i] = i;
        }
        memset(area, 0, sizeof(area));
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%s", tmp);
            for (int j = 0; j < m; j++) {
                if (tmp[j] == '0') {
                    mp[i][j] = false;
                } else {
                    mp[i][j] = true;
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mp[i][j]) {
                    area[z(i, j, 2, 0)] += a0;
                    area[z(i, j, 0, 2)] += a0;
                    area[z(i, j, 0, 0)] += a1;
                } else {
                    area[z(i, j, 0, 0)] += a0;
                    area[z(i, j, 2, 2)] += a0;
                    area[z(i, j, 0, 2)] += a1;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mp[i][j]) {
                    uni(z(i, j, 0, 0), z(i, j, 1, 1));
                    uni(z(i, j, 2, 2), z(i, j, 1, 1));
                } else {
                    uni(z(i, j, 0, 2), z(i, j, 1, 1));
                    uni(z(i, j, 2, 0), z(i, j, 1, 1));
                }
            }
        }
        printf("Case %d:\n", ff);
        int q, u, v;
        cin >> q;
        while (q--) {
            cin >> u >> v;
            printf("%.4lf\n", area[getf(u*105+v)]);
        }
    }
}

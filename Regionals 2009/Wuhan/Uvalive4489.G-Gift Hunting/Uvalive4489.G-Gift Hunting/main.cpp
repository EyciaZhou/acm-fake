//
//  main.cpp
//  Uvalive4489.G-Gift Hunting
//
//  Created by eycia on 11/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct {
    int p, h, s;
} ts[305];

int f[505][55][3];

int main(int argc, const char * argv[]) {
    int v1, v2, n, ff=0;
    while (cin >> v1 >> v2 >> n) {
        if (v1 + v2 + n == 0) break;
        ff++;
        for (int i = 0; i < n; i++) {
            cin >> ts[i].p >> ts[i].h >> ts[i].s;
        }
        memset(f, -1, sizeof(f));
        f[0][0][0] = 0;
        int mx = -1;
        bool fl = true;
        for (int i = 0; i < n; i++) {
            bool fl2 = false;
            for (int j = v1; j >= 0; j--) {
                for (int k = v2; k >= 0; k--) {
                    for (int pr = 1; pr >= 0; pr--) {
                        if (ts[i].s) {
                            int tmp = -2;
                            if (j-ts[i].p >= 0 && f[j-ts[i].p][k][pr] >= 0) {
                                tmp = max(tmp, f[j-ts[i].p][k][pr] + ts[i].h);
                            }
                            if (k-ts[i].p >= 0 && f[j][k-ts[i].p][pr] >= 0) {
                                tmp = max(tmp, f[j][k-ts[i].p][pr] + ts[i].h);
                            }
                            if (pr-1 >= 0 && f[j][k][pr-1] >= 0) {
                                tmp = max(tmp, f[j][k][pr-1] + ts[i].h);
                            }
                            f[j][k][pr] = tmp;
                            continue;
                        }
                        int tmp = f[j][k][pr];
                        if (j-ts[i].p >= 0 && f[j-ts[i].p][k][pr] >= 0 && f[j-ts[i].p][k][pr] + ts[i].h > f[j][k][pr]) {
                            tmp = max(tmp, f[j-ts[i].p][k][pr] + ts[i].h);
                        }
                        if (k-ts[i].p >= 0 && f[j][k-ts[i].p][pr] >= 0 && f[j][k-ts[i].p][pr] + ts[i].h > f[j][k][pr]) {
                            tmp = max(tmp, f[j][k-ts[i].p][pr] + ts[i].h);
                        }
                        if (pr-1 >= 0 && f[j][k][pr-1] >= 0 && f[j][k][pr-1] + ts[i].h > f[j][k][pr]) {
                            tmp = max(tmp, f[j][k][pr-1] + ts[i].h);
                        }
                        f[j][k][pr] = tmp;
                    }
                }
            }
        }
        for (int j = 0; j <= v1; j++) {
            for (int k = 0; k <= v2; k++) {
                for (int pr = 0; pr <= 1; pr++) {
                    mx = max(mx, f[j][k][pr]);
                }
            }
        }
        printf("Case %d: %d\n\n", ff, mx);
    }
}
/*
 3 2 4
 3 10 1
 2 10 1
 5 100 1
 5 80 1
*/
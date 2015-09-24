//
//  main.cpp
//  Sosjo3.c
//
//  Created by eycia on 6/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;

int a[1000005];
int b[1000005];
//int v[10000005];
map<int, int> v;
int m, q, ll, rr;

int main(int argc, const char * argv[]) {
    while (scanf("%d %d", &m, &q) != EOF) {
        if (m == 0 && q == 0) break;
        memset(b, 0, sizeof(b));
        v.clear();
        for (int i = 1; i <= m; i++) {
            scanf("%d", &a[i]);
        }
        b[m] = 11000005;
        v[a[m]] = m;
        for (int i = m-1; i >= 1; i--) {
            b[i] = b[i+1];
            if (v[a[i]] > 0) {
                b[i] = min(b[i+1], v[a[i]]);
            }
            v[a[i]] = i;
        }
        for (int i = 0; i < q; i++) {
            scanf("%d %d", &ll, &rr);
            //cout << b[ll] << " " << rr << endl;
            if (rr < b[ll]) {
                printf("OK\n");
            } else {
                printf("%d\n", a[b[ll]]);
            }
        }
        printf("\n");
    }
}

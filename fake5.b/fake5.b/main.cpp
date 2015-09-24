//
//  main.cpp
//  fake5.b
//
//  Created by eycia on 3/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int a[100005];
bool v[100005];
int pre[100005];
int f[100005];

int main(int argc, const char * argv[]) {
    int n;
    while (scanf("%d", &n) != EOF) {
        memset(a, 0, sizeof(a));
        memset(v, false, sizeof(v));
        memset(pre, 0, sizeof(pre));
        memset(f, 0, sizeof(f));
        
        if (n == 0) return 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        int mm = 0;
        for (int i = 0; i < n; i++) {
            if (v[a[i]]) {
                if (a[i] == 999) {
                    f[i] = max(f[i-1], f[pre[a[i]]]+3);
                } else {
                    f[i] = max(f[i-1], f[pre[a[i]]]+1);
                }
                pre[a[i]] = i;
                if (f[i] > mm) {
                    mm = f[i];
                }
            } else {
                f[i] = mm;
                pre[a[i]] = i;
                v[a[i]] = true;
            }
        }
        int mx = 0;
        for (int i = 0; i < n; i++) {
            if (f[i] > mx) {
                mx = f[i];
            }
        }
        printf("%d\n", mx);
    }
}

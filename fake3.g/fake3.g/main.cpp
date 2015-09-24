//
//  main.cpp
//  fake3.g
//
//  Created by eycia on 30/7/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int a[20005];

int main(int argc, const char * argv[]) {
    int t, n, k, mi;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        sort(a, a+n);
        mi = 0x7fffffff;
        for (int i = 0; i <= n-k; i++) {
            mi = min(mi, a[i+k-1] - a[i]);
        }
        cout << mi << endl;
    }
}

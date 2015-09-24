//
//  main.cpp
//  Sosjo.b
//
//  Created by eycia on 4/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

vector<int> k;

int main(int argc, const char * argv[]) {
    int t, n, a, b, c;
    cin >> t;
    for (int ff = 1; ff <= t; ff++) {
        cin >> n;
        k.clear();
        for (int i = 0; i < n-1; i++) {
            cin >> a >> b >> c;
            k.push_back(c);
        }
        if (n == 2) {
            printf("Case %d: %d\n", ff, k[0]);
            continue;
        }
        if (n < 2) {
            printf("Case %d: %d\n", ff, 0);
            continue;
        }
        sort(k.begin(), k.end());
        printf("Case %d: %d\n", ff, k[k.size()-1] + k[k.size()-2]);
    }
}

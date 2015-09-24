//
//  main.cpp
//  Sosjo.d
//
//  Created by eycia on 4/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>

long long c[10005][10005];

void genc() {
    memset(c, 0, sizeof(c));
    c[1][1] = 1;
    for (int i = 2; i <= 54; i++) {
        for (int j = 1; j <= i; j++) {
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
        }
    }
    for (int i = 1; i <= 54; i++) {
        for(int j = 1; j <= i; j++) {
            c[i-1][j-1] = c[i][j];
        }
    }
}

#define catalan(n) c[2*n][n]-c[2*n][n+1]

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

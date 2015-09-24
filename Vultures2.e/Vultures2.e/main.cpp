//
//  main.cpp
//  Vultures2.e
//
//  Created by eycia on 10/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

char tmp[1005];

long long f[1005][1005];
long long g[1005][1005];

const long long MOD = 1000000007;

int main(int argc, const char * argv[]) {
    while (gets(tmp+2)) {
        int n = strlen(tmp+2)+1;
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        for (int i = 0; i <= n; i++) {
            f[1][1] = 1;
            g[1][1] = 1;
        }
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                if (tmp[i] == 'I') {
                    f[i][j] = g[i-1][j-1];
                }
                if (tmp[i] == 'D') {
                    f[i][j] = (g[i-1][i-1] - g[i-1][j-1] + MOD) % MOD;
                }
                if (tmp[i] == '?') {
                    f[i][j] = g[i-1][i-1];
                }
                g[i][j] = (g[i][j-1] + f[i][j]) % MOD;
            }
        }
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = (ans + f[n][i]) % MOD;
        }
        
        cout << ans << endl;
    }
}

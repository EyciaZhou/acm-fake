//
//  main.cpp
//  Vultures2.i
//
//  Created by eycia on 10/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector<long long> vv;

const long long MOD = 1000000007;
//30^(MOD-2) % MOD = 233333335
const long long mu  = 233333335;

inline long long pp(long long v) {
    return v * v % MOD * v % MOD * v % MOD;
}

long long f(long long n) {
    //sigma 1~n i^4 MOD
    //n(n+1)(2n+1)(3n^2+3n-1)/30
    long long up = n * (n+1) % MOD * (2*n+1) % MOD * ((3 * n * n % MOD + 3 * n - 1) % MOD) % MOD;

    long long d = ((up + MOD) * mu) % MOD;
    
    return d;
}

bool is_p(int p) {
    for (int i = 2; i <= sqrt(p); i++) {
        if (p % i == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, const char * argv[]) {
    
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        if (n == 1) {
            printf("1\n");
            continue;
        }
        vv.clear();
        int sn = sqrt(n);
        for (int i = 2; i <= sn; i++) {
            if (n % i == 0) {
                if (is_p(i)) {
                    vv.push_back(i);
                }
                if (i != n/i) {
                    if (is_p(n/i)) {
                        vv.push_back(n/i);
                    }
                }
            }
        }
        
        long long ans = 0;
        
        int vs = vv.size();
        for (int msk=1; msk<(1<<vs); msk++) {
            int mul = 1, m2 = 1, bits = 0;
            for (int i = 0; i < vs; i++) {
                if (msk & (1<<i)) {
                    bits++;
                    mul = (mul * pp(vv[i])) % MOD;
                    m2 = (m2 * vv[i]) % MOD;
                }
            }
            if (bits % 2 == 1)
                ans = (ans + mul * f((n-1)/m2)) % MOD;
            else
                ans = (ans - mul * f((n-1)/m2) % MOD + MOD) % MOD;
        }
        cout << (f(n-1) - ans + MOD) % MOD << endl;
    }
}

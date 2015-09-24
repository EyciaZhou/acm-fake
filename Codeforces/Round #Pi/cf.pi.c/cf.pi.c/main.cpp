//
//  main.cpp
//  cf.pi.c
//
//  Created by eycia on 6/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <map>
#include <cstdio>
#include <vector>
using namespace std;

map<long long, long long> m1;
map<long long, long long> m2;
vector<long long> ve;

int main(int argc, const char * argv[]) {
    long long n, k;
    int tmp;
    cin >> n >> k;
    long long k2 = k*k;
    for (int i = 0; i < n; i++) {
        scanf("%d", &tmp);
        ve.push_back(tmp);
        m2[tmp]++;
    }
    unsigned long long tot = 0;
    for (int i = 0; i < ve.size(); i++) {
        m2[ve[i]]--;
        if (ve[i] % k == 0) {
            tot += m1[ve[i]/k]*m2[ve[i]*k];
        }
        m1[ve[i]]++;
    }
    cout << tot << endl;
}
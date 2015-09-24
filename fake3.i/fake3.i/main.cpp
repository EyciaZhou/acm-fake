//
//  main.cpp
//  fake3.i
//
//  Created by eycia on 30/7/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <set>
using namespace std;

set<long long> ss;

#define ll long long

ll p;

int pri[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};


void tr2(ll rest, int mx, long long mul) {
    if (rest == 0) {
        ss.insert(mul % p);
        return;
    }
    for (int i = mx; i <= rest; i++) {
        tr2(rest-i, i, mul*i);
    }
}


void tr(ll rest, int rank, ll mul) {
    if (rest == 0) {
        ss.insert(mul%p);
        return;
    }
    if (pri[rank] > rest) return;
    if (rest >= pri[rank]) {
        tr(rest-pri[rank], rank, mul*pri[rank]);
    }
    tr(rest, rank+1, mul);
}

int main(int argc, const char * argv[]) {
    int n, t;
    cin >> t;
    while (t--) {
        cin >> n >> p;
        ss.clear();
        tr(n, 0, 1);/*
        for (set<long long>::iterator it = ss.begin(); it != ss.end(); it++) {
            cout << *it << endl;
        }*/
        cout << ss.size() << endl;
        //ss.clear();
        //tr2(n, 1, 1);
        /*
                     for (set<long long>::iterator it = ss.begin(); it != ss.end(); it++) {
                     cout << *it << endl;
                     }*/
        //cout << ss.size() << endl;
    }
}
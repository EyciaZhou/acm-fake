//
//  main.cpp
//  fake2.f
//
//  Created by eycia on 29/7/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <set>
#include <vector>
#include <cmath>
#include <array>
using namespace std;

int t = 6;

int tab[50][50];

set<array<int, 50> > ss;

array<int, 50> ans;

int cnt = 0;

void pr() {/*
    for (int i = 1; i <= t; i++) {
        for (int j = 1; j <= t; j++) {
            cout << tab[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
    */
    for (int i = 1; i <= t; i++) {
        ans[i-1] = 0;
        for (int j = 1; j <= t; j++) {
            ans[i-1] += tab[i][j];
        }
    }
    sort(ans.begin(), ans.begin()+t);
    ss.insert(ans);
}

void tr(int i, int j) {
    if (i == t+1) {
        pr();
        return ;
    }
    tab[i][j] = 1;
    tab[j][i] = 2;
    if (j < i-1) {
        tr(i, j+1);
    } else {
        tr(i+1, 1);
    }
    
    tab[i][j] = 2;
    tab[j][i] = 1;
    if (j < i-1) {
        tr(i, j+1);
    } else {
        tr(i+1, 1);
    }
    
    tab[i][j] = 3;
    tab[j][i] = 0;
    if (j < i-1) {
        tr(i, j+1);
    } else {
        tr(i+1, 1);
    }
    
    tab[i][j] = 0;
    tab[j][i] = 3;
    if (j < i-1) {
        tr(i, j+1);
    } else {
        tr(i+1, 1);
    }
}

int main(int argc, const char * argv[]) {
    tr(1, 2);
    cout << ss.size() << endl;
    cout << cnt * 3 << endl;
    cout << log(256)/log(2) << endl;
    
    cout << log(16384)/log(2) << endl;
    
    cout << log(4194304)/log(2) << endl;
    
    cout << (long long)(pow(2, 28)-1) / 3 << endl;
    
}

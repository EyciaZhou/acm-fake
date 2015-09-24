//
//  main.cpp
//  Vultures.g
//
//  Created by eycia on 7/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
using namespace std;

#define eps 1e-8
#define ll long long

vector<tuple<int, int, int> > gg;

int main(int argc, const char * argv[]) {
    long long t, hh, ww;
    cin >> t;
    
    
    for (int i = 0; i <= 500; i++) {
        for (int j = 0; j <= 500; j++) {
            double sq = sqrt(i*i+j*j);
            if (sq - (int)sq > eps) continue;
            gg.push_back(make_tuple(i, j, sq));
        }
    }
    
    int gz = gg.size();
    
    for (int ff = 1; ff <= t; ff++) {
        cin >> hh >> ww;
        long long tot = 0;
        
        for (int i = 0; i < gz; i++) {
            for (int r = 1; r < get<2>(gg[i]); r++) {
                int r2 = get<2>(gg[i]) - r;
                
                int ii = get<0>(gg[i]);
                int jj = get<1>(gg[i]);
                
                ll le = min(jj-r2, -r), ri = max(jj+r2, r);
                ll to = min(ii-r2, -r), bo = max(ii+r2, r);
                
                ll h = bo - to;
                ll w = ri - le;
                
                if (h > hh || w > ww) continue;
                if (!(ii == 0 || jj == 0)) {
                    tot += (hh-h+1)*(ww-w+1) * 2;
                } else {
                    tot += (hh-h+1)*(ww-w+1);
                }
            }
        }
        printf("Case %d: %lld\n", ff, tot);
    }
}

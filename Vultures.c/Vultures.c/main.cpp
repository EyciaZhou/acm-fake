//
//  main.cpp
//  Vultures.c
//
//  Created by eycia on 7/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

#define eps 1e-8

long long co[70][70];

void genc() {
    memset(co, 0, sizeof(co));
    co[1][1] = 1;
    for (int i = 2; i <= 69; i++) {
        for (int j = 1; j <= i; j++) {
            co[i][j] = (co[i-1][j] + co[i-1][j-1]);
            //cout << co[i][j] << endl;
        }
    }
    for (int i = 1; i <= 69; i++) {
        for(int j = 1; j <= i; j++) {
            co[i-1][j-1] = co[i][j];
        }
    }
}

int aa, bb, cc, dd;

double dp[15][15][15][15][2][2][2][2][2];
bool v[15][15][15][15][2][2][2][2][2];

double dfs(int a, int b, int c, int d, int ra, int rb, int rc, int rd, int rj) {
    //if (a >= 14 || b >= 14 || c >= 14 || d >= 14) cout << a << b << c << d << endl;
    if (v[a][b][c][d][ra][rb][rc][rd][rj]) {
        return dp[a][b][c][d][ra][rb][rc][rd][rj];
    }
    
    double tot = 0;
    if (a+ra >= aa && b+rb >= bb && c+rc >= cc && d+rd >= dd) {
        //printf("%d %d %d %d %d %d %d %d %d %lf\n", a, b, c, d, 2-rj, ra, rb, rc, rd, co[13][a]*co[13][b]*co[13][c]*co[13][d]*co[2][2-rj]*(a+b+c+d+2-rj)/(co[54][a+b+c+d+2-rj]+0.0));
        return a+b+c+d+2-rj;
        //return co[13][a]*co[13][b]*co[13][c]*co[13][d]*co[2][2-rj]*(a+b+c+d+2-rj)/(co[54][a+b+c+d+2-rj]+0.0);
    }
    if (a < 13) {
        tot += dfs(a+1, b, c, d, ra, rb, rc, rd, rj) * (13-a) / (54-a-b-c-d-2+rj);
    }
    if (b < 13) {
        tot += dfs(a, b+1, c, d, ra, rb, rc, rd, rj) * (13-b) / (54-a-b-c-d-2+rj);
    }
    if (c < 13) {
        tot += dfs(a, b, c+1, d, ra, rb, rc, rd, rj) * (13-c) / (54-a-b-c-d-2+rj);
    }
    if (d < 13) {
        tot += dfs(a, b, c, d+1, ra, rb, rc, rd, rj) * (13-d) / (54-a-b-c-d-2+rj);
    }
    if (rj > 0) {
        double vec[4];
        vec[0] = dfs(a, b, c, d, ra+1, rb, rc, rd, rj-1) * (rj) / (54-a-b-c-d-2+rj);
        vec[1] = dfs(a, b, c, d, ra, rb+1, rc, rd, rj-1) * (rj) / (54-a-b-c-d-2+rj);
        vec[2] = dfs(a, b, c, d, ra, rb, rc+1, rd, rj-1) * (rj) / (54-a-b-c-d-2+rj);
        vec[3] = dfs(a, b, c, d, ra, rb, rc, rd+1, rj-1) * (rj) / (54-a-b-c-d-2+rj);
        sort(vec, vec+4);
        int k = 0;
        while (vec[k] < eps && k < 3) k++;
        tot += vec[k];
    }
    v[a][b][c][d][ra][rb][rc][rd][rj] = true;
    dp[a][b][c][d][ra][rb][rc][rd][rj] = tot;
    return tot;
}

int main(int argc, const char * argv[]) {
    genc();
    int t;
    cin >> t;
    for (int ff = 1; ff <= t; ff++) {
        memset(v, false, sizeof(v));
        memset(dp, 0, sizeof(0));
        vector<int> cd;
        for (int i = 0; i < 4; i++) {
            cin >> aa;
            cd.push_back(aa);
        }
        sort(cd.begin(), cd.end());
        if (cd[3] > 15 || cd[2]+cd[3] > 28 || cd[1] > 13) {
            printf("Case %d: -1.000\n", ff);
            continue;
        }
        aa = cd[0];
        bb = cd[1];
        cc = cd[2];
        dd = cd[3];
        printf("Case %d: %.3lf\n", ff, dfs(0, 0, 0, 0, 0, 0, 0, 0, 2));
        //cout << dfs(0, 0, 0, 0, 0, 0, 0, 0, 2) << endl;
    }
}

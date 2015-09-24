//
//  main.cpp
//  Sosjo3.h
//
//  Created by eycia on 6/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

vector<pair<int, int> > p1;
vector<pair<int, int> > p2;
vector<pair<int, int> > p3;
vector<pair<int, int> > p4;
char tmp[10005];
char m[1005][1005];

int main(int argc, const char * argv[]) {
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        p1.clear();
        p2.clear();
        p3.clear();
        p4.clear();
        for (int i = 0; i < n; i++) {
            scanf("%s", tmp);
            for (int j = 0; j < n; j++) {
                if (tmp[j] == 'O') {
                    p1.push_back({i, j});
                    p2.push_back({j, n-i-1});
                    p3.push_back({n-i-1, n-j-1});
                    p4.push_back({n-j-1, i});
                }
            }
        }
        sort(p1.begin(), p1.end());
        sort(p2.begin(), p2.end());
        sort(p3.begin(), p3.end());
        sort(p4.begin(), p4.end());
        
        for (int i = 0; i < n; i++) {
            scanf("%s", m[i]);
        }
        
        for (int i = 0; i < p1.size(); i++) {
            putchar(m[p1[i].first][p1[i].second]);
        }
        for (int i = 0; i < p2.size(); i++) {
            putchar(m[p2[i].first][p2[i].second]);
        }
        for (int i = 0; i < p3.size(); i++) {
            putchar(m[p3[i].first][p3[i].second]);
        }
        for (int i = 0; i < p4.size(); i++) {
            putchar(m[p4[i].first][p4[i].second]);
        }
        putchar('\n');
    }
}

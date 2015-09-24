//
//  main.cpp
//  Uvalive5691.J-Oil Skimming
//
//  Created by eycia on 13/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#define __maxNodes 400000
using namespace std;

vector<int> G[__maxNodes];
typedef vector<int>::iterator iterator_t;

int num_nodes;
int num_left;
int num_right;
int num_edges;

int matching[__maxNodes];
int check[__maxNodes];

bool dfs(int u) {
    for (iterator_t i = G[u].begin(); i != G[u].end(); i++) {
        int v = *i;
        if (!check[v]) {
            check[v] = true;
            if (matching[v] < 0 || dfs(matching[v])) {
                matching[v] = u;
                matching[u] = v;
                return true;
            }
        }
    }
    return false;
}

int xyl_dfs() {
    int ans = 0;
    memset(matching, -1, sizeof(matching));
    for (int u = 0; u < num_left; u++) {
        if (matching[u] == -1) {
            memset(check, 0, sizeof(check));
            if (dfs(u)) {
                ans++;
            }
        }
    }
    return ans;
}

char mp[1000][1000];

int main(int argc, const char * argv[]) {
    int t;
    scanf("%d", &t);
    for (int ff = 1; ff <= t; ff++) {
        int n;
        scanf("%d", &n);
        memset(mp, '.', sizeof(mp));
        for (int i = 0; i < n; i++) {
            scanf("%s", mp[i]);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mp[i][j] == '#') {
                    if (mp[i+1][j] == '#') {
                        G[i*n+j].push_back((i+1)*n+j);
                        G[(i+1)*n+j].push_back(i*n+j);
                    }
                    if (mp[i][j+1] == '#') {
                        G[i*n+j].push_back(i*n+j+1);
                        G[i*n+j+1].push_back(i*n+j);
                    }
                }
            }
        }
        num_left = n*n+n;
        printf("Case %d: %d\n", ff, xyl_dfs());
        for (int i = 0; i < n*n+n; i++) {
            G[i].clear();
        }
    }
}

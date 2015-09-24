//
//  main.cpp
//  Sosjo.i
//
//  Created by eycia on 4/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#define __maxNodes 110000
using namespace std;

vector<int> G[__maxNodes];
typedef vector<int>::iterator iterator_t;

int num_left;

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

vector<int> an;

int xyl_dfs() {
    int ans = 0;
    memset(matching, -1, sizeof(matching));
    for (int u = num_left - 1; u >= 0; u--) {
        if (matching[u] == -1) {
            memset(check, 0, sizeof(check));
            if (dfs(u)) {
                an.push_back(u+1);
                ans++;
            }
        }
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    int t, n, lf, ri;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < __maxNodes; i++) {
            G[i].clear();
        }
        an.clear();
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &lf, &ri);
            for (int k = lf; k <= ri; k++) {
                G[i].push_back(100+k);
                G[100+k].push_back(i);
            }
        }
        num_left = n;
        cout << xyl_dfs() << endl;
        if (an.size() != 0) {
            for (int i = an.size()-1; i >= 1; i--) {
                cout << an[i] << " ";
            }
            cout << an[0] << endl;
        }
    }
}

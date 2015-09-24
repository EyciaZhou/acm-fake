//
//  main.cpp
//  Vultures.j
//
//  Created by eycia on 7/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

int val[105];
vector<int> g[105];

int main(int argc, const char * argv[]) {
    int t, u, v;
    cin >> t;
    for (int ff = 1; ff <= t; ff++) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < 105; i++) {
            g[i].clear();
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &val[i]);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &u, &v);
            g[u].push_back(v);
        }
        int cur = 0;
        int mx, to;
        int tot = 0;
        while (g[cur].size()) {
            mx = -10;
            to = 0;
            for (int i = 0; i < g[cur].size(); i++) {
                if (val[g[cur][i]] > mx) {
                    mx = val[g[cur][i]];
                    to = g[cur][i];
                }
            }
            tot += mx;
            cur = to;
        }
        printf("Case %d: %d %d\n", ff, tot, cur);
    }
}

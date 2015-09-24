//
//  main.cpp
//  Uvalive5796.H-Hedge Mazes
//
//  Created by eycia on 17/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

vector<int> g[10005];
int vis[10005];
int pre[10005];
int anc[10005];

int fa[10005];

inline int getf(int s) {
    if (fa[s] == s) {
        return s;
    }
    int k = getf(fa[s]);
    fa[s] = k;
    return k;
}

inline void uni(int s, int t) {
    int ss = getf(s);
    int tt = getf(t);
    
    if (ss != tt) {
        fa[tt] = fa[ss];
    }
}

void dfs(int cur, int father, int dep) { // vertex: 0 ~ n-1
    vis[cur] = 1;
    pre[cur] = anc[cur] = dep;
    for (int i = 0; i < g[cur].size(); i++) {
        if (g[cur][i] != father && 1 == vis[g[cur][i]]) {
            if (pre[g[cur][i]] < anc[cur])
                anc[cur] = pre[g[cur][i]];//back edge
        }
        if (0 == vis[g[cur][i]]) { //tree edge
            dfs(g[cur][i], cur, dep+1);
            if (anc[g[cur][i]] < anc[cur])
                anc[cur] = anc[g[cur][i]];
            if (anc[g[cur][i]] > pre[cur]) {
                uni(cur, g[cur][i]);
            }
        }
    }
    vis[cur] = 2;
}

int main(int argc, const char * argv[]) {
    int r, c, q, u, v, s, t;
    while (scanf("%d %d %d", &r, &c, &q) != EOF) {
        if (r == 0 && c == 0 && q == 0) break;
        for (int i = 0; i < 10005; i++) {
            fa[i] = i;
        }
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < 10005; i++) {
            g[i].clear();
        }
        for (int i = 0; i < c; i++) {
            scanf("%d %d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1, -1, 0);
        for (int i = 0; i < q; i++) {
            scanf("%d %d", &s, &t);
            if (getf(s) == getf(t)) {
                puts("Y");
            } else {
                puts("N");
            }
        }
        puts("-");
    }
}

//
//  main.cpp
//  Ural1934.D-Black Spot
//
//  Created by eycia on 13/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

#define mp make_pair

pair<int, double> d[100005];
queue<int> q;
vector<pair<int, double> > g[100005];
bool v[100005];
int pri[100005];

int ss, ee, n, m;

void spfa() {
    while (!q.empty()) q.pop();
    memset(v, false, sizeof(v));
    for (int i = 0; i < n+1; i++) {
        d[i].first = -1;
    }
    q.push(ss);
    v[ss] = true;
    d[ss] = mp(0, 1);
    while (!q.empty()) {
        int k = q.front();
        q.pop();
        v[k] = false;
        
        for (int i = 0; i < g[k].size(); i++) {
            int np = g[k][i].first;
            
            int di = d[k].first + 1, dj = d[np].first;
            
            if (dj == -1) {
                int di = d[k].first + 1;
                double pi = d[k].second * g[k][i].second;
                d[np] = mp(di, pi);
                pri[np] = k;
                if (!v[np]) {
                    v[np] = true;
                    q.push(np);
                }
            } else if (di == dj) {
                double pi = d[k].second * g[k][i].second, pj = d[np].second;
                if (pi > pj) {
                    int di = d[k].first + 1;
                    double pi = d[k].second * g[k][i].second;
                    d[np] = mp(di, pi);
                    pri[np] = k;
                    if (!v[np]) {
                        v[np] = true;
                        q.push(np);
                    }
                }
            }
        }
    }
}

stack<int> ans;

int main(int argc, const char * argv[]) {
    //freopen("/Users/eycia/i", "r", stdin);
    //freopen("/Users/eycia/o", "w", stdout);
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < 100005; i++) {
            g[i].clear();
        }
        scanf("%d %d", &ss, &ee);
        int u, v, w;
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &u, &v, &w);
            g[u].push_back(mp(v, 1-w/100.0));
            g[v].push_back(mp(u, 1-w/100.0));
        }
        swap(ss, ee);
        spfa();
        printf("%d %.8lf\n", d[ee].first+1, 1-d[ee].second);
        
        int cur = ee;
        while (cur != 0) {
            printf("%d ", cur);
            cur = pri[cur];
        }
        
        
        while (!ans.empty()) {
            printf("%d ", ans.top());
            ans.pop();
        }
        putchar('\n');
    }
}
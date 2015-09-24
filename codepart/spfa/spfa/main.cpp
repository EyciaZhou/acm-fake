//
//  main.cpp
//  spfa
//
//  Created by eycia on 6/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define sp_node 100000
#define sp_cost_typ double
vector<pair<int, sp_cost_typ> > g[sp_node];
sp_cost_typ dis[sp_node];
bool v[sp_node];
queue<int> q;

void spfa(int st) {
    for (int i = 0; i < sp_node; i++) dis[i] = -1;
    while (!q.empty()) q.pop();
    
    memset(v, false, sizeof(v));
    dis[st] = 0;
    v[st] = true;
    q.push(st);
    while (!q.empty()) {
        int k = q.front();
        q.pop();
        
        v[k] = false;
        for (int i = 0; i < g[k].size(); i++) {
            if ((dis[k] + g[k][i].second < dis[g[k][i].first] || dis[g[k][i].first] < 0)) {
                dis[g[k][i].first] = dis[k] + g[k][i].second;
                if (!v[g[k][i].first]) {
                    q.push(g[k][i].first);
                    v[g[k][i].first] = true;
                }
            }
        }
    }
}

//
//  main.cpp
//  cf.pi.e
//
//  Created by eycia on 6/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <stack>
#include <queue>
using namespace std;

int n, m;

#define V 100005
int anc[V], pre[V], vis[V];
vector<int> g[V];
vector<int> gid[V];

bool table[V];

string ts(int v) {
    stringstream ss;
    ss<<v;
    return ss.str();
}

void dfs(int cur, int father, int dep) { // vertex: 0 ~ n-1
    vis[cur] = 1;
    pre[cur] = anc[cur] = dep;
    for (int i = 0; i < g[cur].size(); i++) {
        if (gid[cur][i] != father && 1 == vis[g[cur][i]]) {
            if (pre[g[cur][i]] < anc[cur])
                anc[cur] = pre[g[cur][i]];//back edge
        }
        if (0 == vis[g[cur][i]]) { //tree edge
            dfs(g[cur][i], gid[cur][i], dep+1);
            if (anc[g[cur][i]] < anc[cur])
                anc[cur] = anc[g[cur][i]];
            if (anc[g[cur][i]] > pre[cur]) {
                table[gid[cur][i]] = true;
            }
        }
    }
    vis[cur] = 2;
}

#define dijk_V 100005
#define sp_cost_typ long long

#define g h
#define v vsp
#define d dis
vector<pair<int, sp_cost_typ> > g[dijk_V];
sp_cost_typ d[dijk_V];
//int pri[dijk_V];
bool v[dijk_V];

priority_queue<pair<sp_cost_typ, int>, vector<pair<sp_cost_typ, int> >, greater<pair<sp_cost_typ, int> > > p;

void dijk(int st, int n) {
    while (!p.empty()) p.pop();
    memset(d, -1, sizeof(d));
    memset(v, false, sizeof(v));
    d[st] = 0;
    v[st] = true;
    for (int i = 0; i < g[st].size(); i++) {
        if (d[g[st][i].first] > d[st] + g[st][i].second || d[g[st][i].first] == -1) {
            d[g[st][i].first] = d[st] + g[st][i].second;
            p.push({d[g[st][i].first], g[st][i].first});
        }
    }
    for (int i = 0; i < n; i++) { //no matter about the bound, the number only matters
        int k;
        if (p.empty()) continue;
        do {
            pair<int, int> t = p.top();
            p.pop();k = t.second;
        } while (!p.empty() && v[k]);
        for (int j = 0; j < g[k].size(); j++) {
#define uu k
#define vv g[k][j].first
#define ww g[k][j].second
            if (d[vv] > d[uu] + ww || d[vv] == -1) {
                d[vv] = d[uu] + ww;
                p.push({d[vv], vv});
//                pri[vv] = uu;
            }
        }
        v[k] = true;
    }
}
#undef g
#undef v
#undef d


#define g f
#define v vsp2
#define d dis2
#define dijk_V 100005
#define sp_cost_typ long long
vector<pair<int, sp_cost_typ> > g[dijk_V];
sp_cost_typ d[dijk_V];
//int pri[dijk_V];
bool v[dijk_V];

//priority_queue<pair<int, int> > p;

void dijk2(int st, int n) {
    while (!p.empty()) p.pop();
    memset(d, -1, sizeof(d));
    memset(v, false, sizeof(v));
    d[st] = 0;
    v[st] = true;
    for (int i = 0; i < g[st].size(); i++) {
        if (d[g[st][i].first] > d[st] + g[st][i].second || d[g[st][i].first] == -1) {
            d[g[st][i].first] = d[st] + g[st][i].second;
            p.push({d[g[st][i].first], g[st][i].first});
        }
    }
    for (int i = 0; i < n; i++) { //no matter about the bound, the number only matters
        int k;
        if (p.empty()) continue;
        do {
            pair<int, int> t = p.top();
            p.pop();k = t.second;
        } while (!p.empty() && v[k]);
        for (int j = 0; j < g[k].size(); j++) {
#define uu k
#define vv g[k][j].first
#define ww g[k][j].second
            if (d[vv] > d[uu] + ww || d[vv] == -1) {
                d[vv] = d[uu] + ww;
                p.push({d[vv], vv});
                //                pri[vv] = uu;
            }
        }
        v[k] = true;
    }
}
#undef g
#undef v

vector<int> hid[V];
string ans[V];

int main(int argc, const char * argv[]) {
    int s, t, u, v, w;
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        h[u].push_back({v, w});
        f[v].push_back({u, w});
        hid[u].push_back(i);
    }
    dijk(s, n);
    dijk2(t, n);
    
    //if (dis[t] > 0)
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < h[i].size(); j++) {
            //cout << dis2[h[i][j].first] << " " << dis[i] << " " << dis[t]-dis2[h[i][j].first]-dis[i] << " " << h[i][j].second << endl;
            if (dis[i] < 0 || dis2[h[i][j].first] < 0) continue;
            if (dis[t]-dis2[h[i][j].first]-dis[i]==h[i][j].second) {
                g[i].push_back(h[i][j].first);
                g[h[i][j].first].push_back(i);
                gid[i].push_back(hid[i][j]);
                gid[h[i][j].first].push_back(hid[i][j]);
            }
        }
    }
    dfs(s, -1, 0);
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < h[i].size(); j++) {
            if (table[hid[i][j]]) {
                ans[hid[i][j]] = "YES";
            } else if (-(dis[t]-dis2[h[i][j].first]-dis[i])+1 >= 0 ||
                       dis2[h[i][j].first] < 0 || dis[i] < 0) {
                ans[hid[i][j]] = "NO";
            } else {
                ans[hid[i][j]] = "CAN " + ts(h[i][j].second-(dis[t]-dis2[h[i][j].first]-dis[i])+1);
            }
        }
    }
    
    for (int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }
}
/*
 6 6 1 6
 1 2 1
 2 3 1
 2 5 10000
 3 4 10000
 5 4 1
 4 6 1
*/
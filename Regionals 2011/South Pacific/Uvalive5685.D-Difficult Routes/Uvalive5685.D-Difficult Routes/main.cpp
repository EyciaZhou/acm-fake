//
//  main.cpp
//  Uvalive5685.D-Difficult Routes
//
//  Created by eycia on 13/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <tuple>
#include <cmath>
#include <queue>
using namespace std;

struct po {int x, y, z; po(int x,int y,int z):x(x),y(y),z(z){}};
struct edge {
    int v, d;
    double w;
    edge(int v, int d, double w):v(v),d(d),w(w){}
};

vector<po> vs;

inline double gdi(int le, int ri) {
    int runx = vs[ri].x - vs[le].x;
    int runy = vs[ri].y - vs[le].y;
    int runz = vs[ri].z - vs[le].z;
    return sqrt(runx*runx+runy*runy+runz*runz);
}

inline int gd(int le, int ri) {
    int rise = vs[ri].z - vs[le].z;
    double runx = vs[ri].x - vs[le].x;
    double runy = vs[ri].y - vs[le].y;
    double run = sqrt(runx*runx+runy*runy);
    int d = 100*rise/run;
    return d;
}

#define sp_node 30005
#define sp_cost_typ double
vector<edge > g[sp_node];
vector<edge > g2[sp_node];
sp_cost_typ dis[sp_node];
sp_cost_typ dis2[sp_node];
bool v[sp_node];
queue<int> q;

void spfa(int st, int en) {
    for (int i = 0; i < sp_node; i++) dis[i] = -1;
    for (int i = 0; i < sp_node; i++) dis2[i] = -1;
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
            if ((dis[k] + g[k][i].w < dis[g[k][i].v] || dis[g[k][i].v] < 0)) {
                dis[g[k][i].v] = dis[k] + g[k][i].w;
                if (!v[g[k][i].v]) {
                    q.push(g[k][i].v);
                    v[g[k][i].v] = true;
                }
            }
        }
    }
    
    
    //back
#define dis dis2
#define g g2
#define st en
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
            if ((dis[k] + g[k][i].w < dis[g[k][i].v] || dis[g[k][i].v] < 0)) {
                dis[g[k][i].v] = dis[k] + g[k][i].w;
                if (!v[g[k][i].v]) {
                    q.push(g[k][i].v);
                    v[g[k][i].v] = true;
                }
            }
        }
    }
#undef st
#undef g
#undef dis
}

vector<pair<int, int> > tmp;

int main(int argc, const char * argv[]) {
    int n, m, xx, yy, zz, le, ri, st, en, d;
    while (scanf("%d %d", &n, &m) != EOF) {
        if (n == 0 && m == 0) break;
        vs.clear();
        tmp.clear();
        for (int i = 0; i < 30005; i++) {
            g[i].clear();
            g2[i].clear();
        }
        vs.push_back(po(0, 0, 0));
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &xx, &yy, &zz);
            vs.push_back(po(xx, yy, zz));
        }
        
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &le, &ri);
            tmp.push_back(make_pair(le, ri));
        }
        
        scanf("%d %d %d", &st, &en, &d);
        
        for (int i = 0; i < m; i++) {
            le = tmp[i].first;
            ri = tmp[i].second;
            double di = gdi(le, ri);
            if (vs[le].z < vs[ri].z) {
                int dd = gd(le, ri);
                if (dd <= d) {
                    g[le].push_back(edge(ri, dd, di));
                    g2[ri].push_back(edge(le, dd, di));
                }
                g[ri].push_back(edge(le, 0, di));
                g2[le].push_back(edge(ri, 0, di));
            } else if (vs[le].z == vs[ri].z) {
                g[le].push_back(edge(ri, 0, di));
                g2[ri].push_back(edge(le, 0, di));
                g[ri].push_back(edge(le, 0, di));
                g2[le].push_back(edge(ri, 0, di));
            } else {
                int dd = gd(ri, le);
                if (dd <= d) {
                    g[ri].push_back(edge(le, dd, di));
                    g2[le].push_back(edge(ri, dd, di));
                }
                g[le].push_back(edge(ri, 0, di));
                g2[ri].push_back(edge(le, 0, di));
            }
        }
        

        
        spfa(st, en);
        
        double min = (int)0x7fffffff;
        
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < g[i].size(); j++) {
                if (g[i][j].d == d) {
                    if (dis[i] >= 0 && dis2[g[i][j].v] >= 0)
                    if (dis[i] + dis2[g[i][j].v] + g[i][j].w < min) {
                        min = dis[i] + dis2[g[i][j].v] + g[i][j].w;
                    }
                }
            }
        }
        
        if (min == (int)0x7fffffff) {
            puts("None");
        } else {
            printf("%.3f\n", min);
        }
    }
}

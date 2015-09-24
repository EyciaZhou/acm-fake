//
//  main.cpp
//  Uvalive5689.H-Pahom on Water
//
//  Created by eycia on 13/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

double eps = 1e-9;

//base type part
struct po {
    double x, y;
    po() : x(0), y(0) {}
    po(double xx, double yy) : x(xx), y(yy) {}
};

struct vec {
    double x, y;
    vec() : x(0), y(0) {}
    vec(double xx, double yy) : x(xx), y(yy) {}
    vec(po from, po to) : x(to.x - from.x), y(to.y - from.y){}
    double lens() {return sqrt(x * x + y * y);}
    vec vertical() {return vec(-y, x);} //垂直
    vec unit(); //单位
};

struct cir {
    po o;
    double r;
    cir(po o, double r) : o(o), r(r) {}
    bool insi(po &p);   //judge if p inside the cir
    void meet(po &p1, po &p2, po &r1, po &r2); //meet the line on p1, p2 returns r1 r2
    int meet_seg(po &p1, po &p2, po &r1, po &r2); //meet the seg of p1, p2 returns r1 r2 and which
    int meet_cir(cir c, po &r1, po &r2);
    double two_po_ang(po &p1, po &p2);
    int meet_cir_stat(cir &other);
};

// 0:外离 1:内含 2:外切 3:内切 4:相交
int meet_cir_stat(double d, double k, double r) {
    if (r > k) swap(k, r);
    //cout << " aaaa " << d << " " << k << " " << r << endl;
    if (fabs(d-r-k) < eps) return 2;
    if (fabs(d+r-k) < eps) return 3;
    if (d > r+k) return 0;
    if (d < r-k) return 1;
    return 4;
}

int cir::meet_cir_stat(cir &other) {
    vec toward(o, other.o);
    double d = toward.lens(), r1 = r, r2 = other.r;
    return ::meet_cir_stat(d, r1, r2);
}

vector<pair<cir, double> > cs;
vector<int> g[500];

const int N = 605;
const int INF = 0x7fffffff;
int num_node;

int map[N][N];
int pre[N];
int flow_in[N];
int start, en;
std::queue<int> q;

int find_one_bfs() {
    int i, t;
    while (!q.empty()) {
        q.pop();
    }
    memset(pre, -1, sizeof(pre));
    
    pre[start] = 0;
    flow_in[start] = INF;
    
    q.push(start);
    while (!q.empty()) {
        t = q.front();
        q.pop();
        
        if (t == en) {
            break;
        }
        
        for (i = 0; i < num_node; i++) {
            if (pre[i] == -1 &&  map[t][i]) {
                if (flow_in[t] < map[t][i]) {
                    flow_in[i] = flow_in[t];
                } else {
                    flow_in[i] = map[t][i];
                }
                q.push(i);
                pre[i] = t;
            }
        }
    }
    if (pre[en] == -1) {
        return -1;
    } else{
        return flow_in[en];
    }
}

int zdl() {
    int max_flow = 0;
    int cf_p;
    int now, prev;
    
    while ((cf_p = find_one_bfs()) != -1) {
        max_flow += cf_p;
        
        now = en;
        
        while (now != start) {
            prev = pre[now];
            map[prev][now] -= cf_p;
            map[now][prev] += cf_p;
            now = prev;
        }
    }
    return max_flow;
}

int main(int argc, const char * argv[]) {
    int ff, xx, yy, rr;
    double co;
    cin >> ff;
    for (int i = 0; i < ff; i++) {
        cs.clear();
        for (int i = 0; i < 500; i++) {
            g[i].clear();
        }
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> co >> xx >> yy >> rr;
            if (co == 400) {
                start = i;
            }
            if (co == 789) {
                en = i;
            }
            cs.push_back({cir(po(xx, yy), rr), co});
        }
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                int st = cs[i].first.meet_cir_stat(cs[j].first);
                //cout << i << " " << cs[i].first.r << " " << j << " " << cs[i].first.r << " " << st << endl;
                if (st == 1 || st == 4) {
                    if (cs[i].second < cs[j].second) {
                        //cout << i << "->" << j << endl;
                        g[i].push_back(j);
                    }
                    if (cs[i].second > cs[j].second) {
                        //cout << j << "-2>" << i << endl;
                        g[j].push_back(i);
                    }
                }
            }
        }
        // = = gened the graph
        memset(map, 0, sizeof(map));
        for (int i = 0; i < n; i++) {
            if (i == start || i == en) {
                map[i][i+n] = 2;
            } else {
                map[i][i+n] = 1;
            }
            for (int j = 0; j < g[i].size(); j++) {
                if (i == start && g[i][j] == en) {
                    map[i+n][g[i][j]] = 2;
                } else {
                    map[i+n][g[i][j]] = 1;
                }
            }
        }
        num_node = 2*n;
        if (zdl() < 2) {
            puts("Game is NOT VALID");
        } else {
            puts("Game is VALID");
        }
    }
}
/*
 2
 2
 400.0 0 0 40
 789.0 7 0 20
 3
500.32 5 0 3
 400.0 0 0 4
 789.0 7 0 2
 500.35 5 0 2

*/
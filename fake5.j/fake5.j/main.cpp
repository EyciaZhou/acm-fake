//
//  main.cpp
//  fake5.j
//
//  Created by eycia on 3/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <queue>
#include <cstring>
#include <string>
#include <map>
using namespace std;

#define N 5000
#define E 20000

#define typef int
#define typec int
const typef inff = 0x3f3f3f3f;
const typec infc = 0x3f3f3f3f;
struct network
{
    int nv, ne, pnt[E], nxt[E];
    int vis[N], que[N], head[N], pv[N], pe[N];
    typef flow, cap[E]; typec cost, dis[E], d[N];
    void addedge(int u, int v, typef c, typec w) {
        pnt[ne] = v; cap[ne] = c;
        dis[ne] = +w; nxt[ne] = head[u]; head[u] = (ne++);
        pnt[ne] = u; cap[ne] = 0;
        dis[ne] = -w; nxt[ne] = head[v]; head[v] = (ne++);
    }
    int mincost(int src, int sink) {
        int i, k, f, r; typef mxf;
        for (flow = 0, cost = 0; ; ) {
            memset(pv, -1, sizeof(pv));
            memset(vis, 0, sizeof(vis));
            for (i = 0; i < nv; ++i) d[i] = -infc;
            d[src] = 0; pv[src] = src; vis[src] = 1;
            for(f=0,r=1,que[0]=src;r!=f;){
                i = que[f++]; vis[i] = 0;
                if (N == f) f = 0;
                for (k = head[i]; k != -1; k = nxt[k]) {
                    if(cap[k] && dis[k]+d[i] > d[pnt[k]])
                    {
                        d[pnt[k]] = dis[k] + d[i];
                        if (0 == vis[pnt[k]]) {
                            vis[pnt[k]] = 1;
                            que[r++] = pnt[k];
                            if (N == r) r = 0;
                        }
                        pv[pnt[k]]=i; pe[pnt[k]]=k;
                    }
                }
            }
            if (-1 == pv[sink]) break;
            for (k = sink, mxf = inff; k != src; k = pv[k]) if (cap[pe[k]] < mxf) mxf = cap[pe[k]];
            flow += mxf; cost += d[sink];
            for (k = sink; k != src; k = pv[k]) { cap[pe[k]] -= mxf; cap[pe[k] ^ 1] += mxf;}
        }
        return cost;
    }
    void build(int v) {
        nv=v;ne=0;
        memset(head, -1, sizeof(head));
    }
}g;

    
int tt[7][9] = {
    {1, 2, 1, 1, 2, 1, 1, 2},
    {1, 2, 1, 1, 3, 1, 1, 1},
    {1, 2, 1, 1, 3, 0, 0, 3},
    {1, 3, 0, 0, 3, 1, 1, 2},
    {1, 3, 0, 0, 4, 1, 1, 1},
    {1, 3, 1, 1, 3, 0, 0, 2},
    {1, 4, 1, 1, 3, 0, 0, 1}};

int mp[505][10];
char tmp[100];


string name[7] = {
	"A","B","C","D","E","F","China"};

int main(int argc, const char * argv[]) {
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) return 0;
		
		memset(mp, 0, sizeof(mp));
        
        for (int i = 0; i < n; i++) {
            scanf("%s %d %d %d %d %d %d %d %d", tmp, &mp[i][0], &mp[i][1], &mp[i][2], &mp[i][3], &mp[i][4], &mp[i][5], &mp[i][6], &mp[i][7]);
        }
        
        int o1 = 2;
        int o2 = n+10;
        int o3 = n*9+10;
        int nn = n*9+30;
		
		int pp = 0, mx = -1;
		
		vector<pair<int, int> > ans;
		
        for (int kk = 0; kk < 7; kk++) {
            g.build(nn);
            for (int i = 0; i < n; i++) {
                g.addedge(0, o1+i, 1, 0);
                for (int j = 0; j < 8; j++) {
                    g.addedge(o1+i, o3+j, 1, mp[i][j]);
                }
            }
            
            for (int i = 0; i < 8; i++) {
                g.addedge(o3+i, nn-1, tt[kk][i], 0);
            }
            g.mincost(0, nn-1);
            //printf("%d %d\n", g.cost, g.flow);
			
			if (g.cost > mx) {
				mx = g.cost;
				pp = kk;
				ans.clear();
				ans.push_back(make_pair(kk, g.cost));
			} else if (g.cost == mx) {
				ans.push_back(make_pair(kk, g.cost));
			}
        }
		
		for (int i = 0; i < ans.size(); i++) {
			printf("Formation %s has the highest points %d.\n", name[ans[i].first].c_str(), ans[i].second);
		}
		printf("\n");
    }
}
//
//  main.cpp
//  Vultures2.f
//
//  Created by eycia on 10/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdio>
using namespace std;

//int mp[205][50005];
char op[20];
int tot[10];

#define lc(a) ((a) << 1)
#define rc(a) ((a) << 1 | 1)

struct OneSegLine {
    //int co[100005];
    char lazy[100005];
    
    void clear() {
        memset(lazy, 0, sizeof(lazy));
    }
    
    int get(int tree, int le, int ll, int rr) {
        //printf("%d %d %d %d %d\n", tree, le, ll, rr, co[tree]);
        if (ll == rr) {
            return lazy[tree];
        }
        
        if (lazy[tree] > 0) {
            lazy[lc(tree)] = lazy[rc(tree)] = lazy[tree];
            lazy[tree] = -1;
        }
        int mid = (ll+rr) / 2;
        if (le >= mid+1) {
            return get(rc(tree), le, mid+1, rr);
        } else {
            return get(lc(tree), le, ll, mid);
        }
    }
    
    void modify(int tree, int le, int ri, int ll, int rr, int c) {
        //printf("%d %d %d %d %d %d\n", tree, le, ri, ll, rr, c);
        if (ll == rr) {
            lazy[tree] = c;
            return;
        }
        if (le == ll && ri == rr) {
            lazy[tree] = c;
            return;
        }
        //push_back
        if (lazy[tree] > 0) {
            lazy[lc(tree)] = lazy[rc(tree)] = lazy[tree];
            lazy[tree] = -1;
        }
        
        int mid = (ll+rr) / 2;
        //ll~mid mid+1~rr
        if (le >= mid+1) {
            modify(rc(tree), le, ri, mid+1, rr, c);
        } else if (ri <= mid) {
            modify(lc(tree), le, ri, ll, mid, c);
        } else {
            modify(lc(tree), le, mid, ll, mid, c);
            modify(rc(tree), mid+1, ri, mid+1, rr, c);
        }
    }
} mp[205];

int inline abs(int a) {
    if (a < 0) return -a;
    return a;
}

int main(int argc, const char * argv[]) {
    int n, m, q;
    int x, y, r, t, c;
    while (scanf("%d %d %d", &n, &m, &q) != EOF) {
        memset(tot, 0, sizeof(tot));
        memset(mp, 0, sizeof(mp));
        for (int i = 0; i < q; i++) {
            scanf("%s", op);
            string o(op);
            if (o == "Diamond") {
                scanf("%d %d %d %d", &x, &y, &r, &c);
                for (int i = x-r; i <= x; i++) {
                    if (i < 0 || i >= n) continue;
                    mp[i].modify(1, max(0, y-(i-x+r)), min(m-1, y+(i-x+r)), 0, m-1, c);
                }
                for (int i = x+1; i <= x+r; i++) {
                    if (i < 0 || i >= n) continue;
                    mp[i].modify(1, max(0, y+(i-x-r)), min(m-1, y-(i-x-r)), 0, m-1, c);
                }
            } else if (o == "Triangle") {
                scanf("%d %d %d %d", &x, &y, &r, &c);
                for (int i = x; i < x+(r+1)/2; i++) {
                    if (i < 0 || i >= n) continue;
                    mp[i].modify(1, max(0, y-(r+1)/2+i-x+1), min(m-1, y+(r+1)/2-i+x-1), 0, m-1, c);
                }
            } else if (o == "Rectangle") {
                scanf("%d %d %d %d %d", &x, &y, &r, &t, &c);
                for (int i = x; i < x+r; i++) {
                    if (i < 0 || i >= n) continue;
                    mp[i].modify(1, max(0, y), min(m-1, y+t-1), 0, m-1, c);
                }
            } else if (o == "Circle") {
                scanf("%d %d %d %d", &x, &y, &r, &c);
                for (int i = x-r; i <= x+r; i++) {
                    if (i < 0 || i >= n) continue;
                    int a = (int)sqrt(r * r - (i-x)*(i-x));
                    mp[i].modify(1, max(0, y-a), min(m-1, a+y), 0, m-1, c);
                }
            }
            /*
             for (int i = 0; i < n; i++) {
             for (int j = 0; j < m; j++) {
             //cout << i << " " << j << endl;
             cout << mp[i].get(1, j, 0, m-1);
             //cout << endl;
             }
             cout << endl;
             }
            */
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                tot[mp[i].get(1, j, 0, m-1)]++;
            }
        }
        for (int i = 1; i < 9; i++) {
            printf("%d ", tot[i]);
        }
        printf("%d\n", tot[9]);
    }
}
/*
 8 8 4
 Diamond 3 3 1 1
 Triangle 4 4 1 2
 */

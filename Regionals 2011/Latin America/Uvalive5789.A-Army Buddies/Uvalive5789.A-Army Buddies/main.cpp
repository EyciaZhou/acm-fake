//
//  main.cpp
//  Uvalive5789.A-Army Buddies
//
//  Created by eycia on 17/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
using namespace std;

int fa[100005];
int fb[100005];

int gfa(int i) {
    if (fa[i] == i) {
        return i;
    }
    int r = gfa(fa[i]);
    fa[i] = r;
    return r;
}

int gfb(int i) {
    if (fb[i] == i) {
        return i;
    }
    int r = gfb(fb[i]);
    fb[i] = r;
    return r;
}

int main(int argc, const char * argv[]) {
    int l, n, ll, rr, tl, tr;
    while (scanf("%d %d", &l, &n) != EOF) {
        if (l == 0 && n == 0) break;
        for (int i = 0; i <= l+1; i++) {
            fa[i] = fb[i] = i;
        }
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &tl, &tr);
            tr;
            tl--;
            ll = tl;
            rr = tr;
            
            while (ll <= rr) {
                ll = gfa(ll);
                if (ll + 1 <= rr) {
                    fa[ll] = ll + 1;
                }
                ll = ll + 1;
            }
            
            ll = tl;
            rr = tr;
            
            while (ll <= rr) {
                rr = gfb(rr);
                if (ll <= rr-1) {
                    fb[rr] = rr-1;
                }
                rr = rr - 1;
            }

            ll = gfa(tl)+1;
            rr = gfb(tr);
            if (rr <= 0) putchar('*'); else printf("%d", rr);
            putchar(' ');
            if (ll > l) putchar('*'); else printf("%d", ll);
            putchar('\n');
        }
        cout << "-" << endl;
    }
}

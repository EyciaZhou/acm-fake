//
//  main.cpp
//  Sosjo.e
//
//  Created by eycia on 4/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

const int N = 310000;
const int tk = 26, tb = 'a';
int top, tree[N][tk+1], mk[N];

void init() {
    top = 1;
    memset(tree[0], 0, sizeof(tree[0]));
}

void insert(char *s) {
    int rt, nxt;
    for (rt = 0; *s; rt = nxt, ++s, tree[rt][tk]++) {
        nxt = tree[rt][*s - tb];
        if (0 == nxt) {
            tree[rt][*s - tb] = nxt = top;
            //cout << *s << " " << top;
            memset(tree[top], 0, sizeof(tree[top]));
            top++;
        }
    }
    
}

int  cnt(char *s, int tre) {
    if (*s == 0 || mk[tre] == 1) {
        if (tre != 0) {
            return tree[tre][tk];
        }
        return 0;
    }
    s++;
    if (*s != 0) {
        if (tree[tre][*s - tb] != 0) {
            return cnt(s, tree[tre][*s - tb]);
        }
        return 0;
    } else {
        return cnt(s, tre);
    }
}

char tmp[50];
double s1[8];
int s2[8];

char gc() {
    for (int i = 0; i < 8; i++) {
        scanf("%lf", &s1[i]);
    }
    bool b = false;
    for (int i = 0; i < 8; i++) {
        s2[i] = int(s1[i] / s1[0] * 2 + 0.5);
        if (s2[i] == 4) b = true;
    }
    if (b) for (int i = 0; i < 8; i++) {
            s2[i] /= 2;
    }
    char c = 0;
    for (int i = 0; i < 8; i++) {
        c = c * 2 + s2[i] - 1;
    }
    return c;
}

int main(int argc, const char * argv[]) {
    int n, m, tot, k;
    while (scanf("%d %d", &n, &m) != EOF) {
        init();
        for (int i = 0; i < n; i++) {
            scanf("%s", tmp);
            insert(tmp);
        }
        tot = 0;
        while (m--) {
            scanf("%d", &k);
            tmp[0] = 'A';
            for (int i = 1; i <= k; i++) {
                tmp[i] = gc();
            }
            tmp[k+1] = 0;
            //puts(tmp);
            tot += cnt(tmp, 0);
            //printf("%d\n", cnt(tmp, 0));
        }
        printf("%d\n", tot);
    }
}
/*
4 3
apple
apple
avatar
book
1
1 2 2 1 1 1 1 2
2
1 2 2 1 1 1 1 2
10.1 20.1 19.9 20.0 10.2 9.8 9.9 10.0
1
1 2 2 1 1 1 2 2
*/
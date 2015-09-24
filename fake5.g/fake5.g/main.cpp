//
//  main.cpp
//  fake5.g
//
//  Created by eycia on 4/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 3100000;
const int tk = 26, tb = 'a';
int top, tree[N][tk+1], mk[N];

void init() {
    top = 1;
    memset(tree, 0, sizeof(tree));
}

void insert(char *s) {
    int rt, nxt;
    for (rt = 0; *s; rt = nxt, ++s, tree[rt][tk]++) {
        nxt = tree[rt][*s - tb];
        if (0 == nxt) {
            tree[rt][*s - tb] = nxt = top;
            memset(tree[top], 0, sizeof(tree[top]));
            top++;
        }
    }
}

char tmp[30];

void mark(char *s, int dis, int tre) {
	if (mk[tre] == 1) {
		return;
	}
    if (*s == 0 || mk[tre] == 1) {
        if (tre != 0) {
			//cout << cac << endl;
            mk[tre]=1;
        }
        return;
    }
    if (dis > 0) {
        //dele
		
		for (int i = 1; i <= dis; i++) {
			char *tmp = s+1+i;
			if (*(tmp) != 0) {
				if (tree[tre][*tmp - tb] != 0) {
					mark(tmp, dis-i, tree[tre][*tmp - tb]);
				}
			} else {
				mark(tmp, dis-i, tre);
			}
		}

        
        //insert
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (tree[tre][ch - tb] != 0) {
                mark(s, dis-1, tree[tre][ch - tb]);
            }
        }
        
        //replace
		if (*(s+1) != 0) {
			for (char ch = 'a'; ch <= 'z'; ch++) {
				if (tree[tre][ch - tb] != 0) {
					mark(s+1, dis-1, tree[tre][ch - tb]);
				}
			}
		} else {
			for (char ch = 'a'; ch <= 'z'; ch++) {
				mark(s+1, dis-1, tre);
			}
		}
    }
    s++;
    if (*s != 0) {
        if (tree[tre][*s - tb] != 0) {
            mark(s, dis, tree[tre][*s - tb]);
        }
    } else {
        mark(s, dis, tre);
    }
}

int coun = 0;

void cnt(char *s, int dis, int tre) {
    if (mk[tre] == -1) {
        return;
    }
    if (mk[tre] == 1 || *s == 0) {
        coun += tree[tre][tk];
        mk[tre] = -1;
        return;
    }
    if (dis > 0) {
        //dele
		for (int i = 1; i <= dis; i++) {
			char *tmp = s+1+i;
			if (*(tmp) != 0) {
				if (tree[tre][*tmp - tb] != 0) {
					cnt(tmp, dis-i, tree[tre][*tmp - tb]);
				}
			} else {
				cnt(tmp, dis-i, tre);
			}
		}
		
        char *tmp = s+2;
        if (*(s+2) != 0) {
            if (tree[tre][*tmp - tb] != 0) {
                cnt(tmp, dis-1, tree[tre][*tmp - tb]);
            }
        } else {
            cnt(tmp, dis-1, tre);
        }
        
        
        //insert
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (tree[tre][ch - tb] != 0) {
                cnt(s, dis-1, tree[tre][ch - tb]);
            }
        }
        
        //replace
		if (*(s+1) != 0) {
			for (char ch = 'a'; ch <= 'z'; ch++) {
				if (tree[tre][ch - tb] != 0) {
					cnt(s+1, dis-1, tree[tre][ch - tb]);
				}
			}
		} else {
			for (char ch = 'a'; ch <= 'z'; ch++) {
				cnt(s+1, dis-1, tre);
			}
		}
    }
    s++;
    if (*s != 0) {
        if (tree[tre][*s - tb] != 0) {
            cnt(s, dis, tree[tre][*s - tb]);
        }
    } else {
        cnt(s, dis, tre);
    }
}

int main(int argc, const char * argv[]) {
    int n, m, dis;
    while (scanf("%d", &n) != EOF) {
        init();
        for (int i = 0; i < n; i++) {
            scanf("%s", tmp);
            insert(tmp);
        }
        scanf("%d", &m);
        while (m--) {
            memset(tmp, 0, sizeof(tmp));
            scanf("%s %d", tmp+1, &dis);
            
            //if (dis >= strlen(tmp+1)) {
            //    cout << 0 << endl;
            //    continue;
            //}
            
            tmp[0] = 'A';
            memset(mk, 0, sizeof(mk));
            mark(tmp, dis, 0);
            coun = 0;
            cnt(tmp, dis, 0);
            printf("%d\n", coun);
        }
    }
}
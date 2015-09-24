//
//  main.cpp
//  fake5.a
//
//  Created by eycia on 3/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

//
//  main.cpp
//  sudoko
//
//  Created by eycia on 14/11/11.
//  Copyright (c) 2014年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char ss[9][9];
int h[9];
int s[9];
int f[9];

void update(int i, int j, int d) {
    h[i] = h[i] | (1 << d);
    s[j] = s[j] | (1 << d);
    f[i / 3 + j / 3 * 3] = f[i / 3 + j / 3 * 3] | (1 << d);
}

void remove(int i, int j, int d) {
    h[i] = h[i] ^(1 << d);
    s[j] = s[j] ^ (1 << d);
    f[i / 3 + j / 3 * 3] = f[i / 3 + j / 3 * 3] ^ (1 << d);
}

bool ok(int i, int j, int d) {
    return !((h[i] & (1 << d)) | (s[j] & (1 << d)) | (f[i / 3 + j / 3 * 3] & (1 << d)));
}

int val[300];
int ans;

void dfs() {
    int tot = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (ss[i][j] >= '1' && ss[i][j] <= '9') {
                tot++;
            }
        }
    }

    if (tot == 81) {/*
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << ss[i][j] << "   ";
            }
            cout << endl;
        }
        cout << endl;*/
        ans++;
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (ss[i][j] == '0') {
                for (int k = 1; k <= 9; k++) {
                    if (ok(i, j, k)) {
                        update(i, j, k);
                        ss[i][j] = k+'0';
                        dfs();
                        ss[i][j] = '0';
                        remove(i, j, k);
                    }
                }
                return;
            }
            if (ss[i][j] >= 'a' && ss[i][j] <= 'z') {
                if (ss[i][j] == 'e') {
                    for (int k = 2; k <= 9; k+=2) {
                        if (ok(i, j, k)) {
                            update(i, j, k);
                            ss[i][j] = k+'0';
                            dfs();
                            ss[i][j] = 'e';
                            remove(i, j, k);
                        }
                    }
                    return;
                } else if (ss[i][j] == 'o') {
                    for (int k = 1; k <= 9; k+=2) {
                        if (ok(i, j, k)) {
                            update(i, j, k);
                            ss[i][j] = k+'0';
                            dfs();
                            ss[i][j] = 'o';
                            remove(i, j, k);
                        }
                    }
                    return;
                } else {
                        if (val[ss[i][j]] == -1) {
                            for (int k = 1; k <= 9; k++) {
                                if (ok(i, j, k)) {
                                    val[ss[i][j]] = k;
                                    update(i, j, k);
                                    char tmp = ss[i][j];
                                    ss[i][j] = k+'0';
                                    dfs();
                                    ss[i][j] = tmp;
                                    remove(i, j, k);
                                    val[ss[i][j]] = -1;
                                }
                            }
                        } else {
                            //cout << ss[i][j] << " " << val[ss[i][j]] << endl;
                            //cout << ok(i, j, val[ss[i][j]]) << endl;
                            if (ok(i, j, val[ss[i][j]])) {
                                int k = val[ss[i][j]];
                                update(i, j, k);
                                char tmp = ss[i][j];
                                ss[i][j] = k+'0';
                                dfs();
                                ss[i][j] = tmp;
                                remove(i, j, k);
                            }
                        }
                        return;
                }
            }
        }
    }
}

char tmp[20];

int main(int argc, const char * argv[]) {
    int t;
    scanf("%d",&t);
    while (t--) {
        ans = 0;
        for (int i = 0; i < 255; i++) {
            val[i] = -1;
        }
        memset(h, 0, sizeof(h));
        memset(s, 0, sizeof(s));
        memset(f, 0, sizeof(f));
        for (int i = 0; i < 9; i++) {
            scanf("%s", tmp);
            for (int j = 0; j < 9; j++) {
                ss[i][j] = tmp[j];
                if (ss[i][j] > '0' && ss[i][j] <= '9') {
                    update(i, j, tmp[j]-'0');
                }
            }
        }
        dfs();
        cout << ans << endl;
    }
}
/*
zcdfghiab
fgbaizcdh
aihcdbzfg
800060003
400803001
700020006
060000280
000419005
000080079
 
534678a12
672195348
198342567
85b761423
4268537a1
713b24856
a61537284
28741b635
34528617z
*/
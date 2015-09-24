//
//  main.cpp
//  Uvalive5797.I-In Braille
//
//  Created by eycia on 17/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

char o[10];
char raw[200];
char mp[3][1000];

char sig[10][10] = {
    {".* ** .. "},
    {"*. .. .. "},
    {"*. *. .. "},
    
    {"** .. .. "},
    {"** .* .. "},
    {"*. .* .. "},
    
    {"** *. .. "},
    {"** ** .. "},
    {"*. ** .. "},
    
    {".* *. .. "}
};

int mk[10] = {
    7,
    8,
    10,
    12,
    13,
    9,
    14,
    15,
    11,
    6};

int mk2[20];

int main(int argc, const char * argv[]) {
    int n;
    for (int i = 0; i < 10; i++) {
        mk2[mk[i]] = i;
    }
    while (cin >> n) {
        if (n == 0) break;
        scanf("%s", o);
        if (o[0] == 'S') {
            scanf("%s", raw);
            int sl = strlen(raw);
            for (int i = 0; i < sl; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        mp[j][i*3+k] = sig[raw[i] - '0'][j*3+k];
                    }
                }
            }
            for (int i = 0; i < 3; i++) {
                mp[i][sl*3-1] = '\0';
                puts(mp[i]);
            }
        } else {
            gets(mp[0]);
            for (int i = 0; i < 3; i++) {
                gets(mp[i]);
            }
			for (int i = 0; i < n; i++) {
                int k = 0;
                k = k*2 + (mp[0][i*3] == '*' ? 1 : 0);
                k = k*2 + (mp[0][i*3+1] == '*' ? 1 : 0);
                k = k*2 + (mp[1][i*3] == '*' ? 1 : 0);
                k = k*2 + (mp[1][i*3+1] == '*' ? 1 : 0);
				
                cout << mk2[k];
                
            }
            cout << endl;
        }
    }
}

//
//  main.cpp
//  Uvalive5799.K-King's Poker
//
//  Created by eycia on 17/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, const char * argv[]) {
    int ca[5];
    while (cin >> ca[0] >> ca[1] >> ca[2]) {
        if (ca[0] == 0 && ca[1] == 0 && ca[2] == 0) break;
        sort(ca, ca+3);
        if (ca[0] == ca[1] && ca[1] == ca[2]) {
            if (ca[0] == 13) {
                puts("*");
            } else {
                printf("%d %d %d\n", ca[0]+1, ca[0]+1, ca[0]+1);
            }
        } else if (ca[0] == ca[1] || ca[1] == ca[2]) {
            int p, a;
            if (ca[0] == ca[1]) {
                p = ca[0];
                a = ca[2];
            } else {
                p = ca[2];
                a = ca[0];
            }
            
            if (a == 13) {
                printf("%d %d %d\n", 1, p+1, p+1);
            } else {
                a++;
                if (a == p) a++;
                if (a == 14) {
                    puts("1 1 1");
                } else {
                    if (a > p) {
                        printf("%d %d %d\n", p, p, a);
                    } else {
                        printf("%d %d %d\n", a, p, p);
                    }
                }
            }
        } else {
            puts("1 1 2");
        }
    }
}

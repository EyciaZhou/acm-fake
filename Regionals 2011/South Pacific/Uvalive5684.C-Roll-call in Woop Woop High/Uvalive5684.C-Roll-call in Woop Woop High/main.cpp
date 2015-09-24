//
//  main.cpp
//  Uvalive5684.C-Roll-call in Woop Woop High
//
//  Created by eycia on 13/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
using namespace std;

char tmp[4000];

int main(int argc, const char * argv[]) {
    int t;
    string name, ans;
    scanf("%d", &t);
    for (int ff = 1; ff <= t; ff++) {
        int n;
        scanf("%d", &n);
        int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
        gets(tmp);
        for (int i = 0; i < n; i++) {
            gets(tmp);
            stringstream ss(tmp);
            ss >> name;
            int tot = 0, yy = 0, nn = 0, flag = 1, f2 = 0;
            while (ss >> ans) {
                tot++;
                if (ans == "y" || ans == "yes") {
                    if (flag) f2 = 1;
                    yy++;
                }
                if (ans == "n" || ans == "no") {
                    nn++;
                }
                flag = 0;
            }
            if (tot == 0) {
                p4++;
                continue;
            }
            if (tot == nn) {
                p3++;
                continue;
            }
            if (f2) {
                p1++;
                continue;
            }
            p2++;
        }
        printf("Roll-call: %d\n", ff);
        printf("Present: %d out of %d\n", p1, n);
        printf("Needs to study at home: %d out of %d\n", p2, n);
        printf("Needs remedial work after school: %d out of %d\n", p3, n);
        printf("Absent: %d out of %d\n", p4, n);
    }
}

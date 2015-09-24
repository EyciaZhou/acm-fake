//
//  main.cpp
//  Uvalive5683.B-Avoiding a disaster
//
//  Created by eycia on 13/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> vec;

int main(int argc, const char * argv[]) {
    int t, hh, mm;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        vec.clear();
        for (int i = 0; i < 3; i++) {
            scanf("%d:%d", &hh, &mm);
            vec.push_back((hh*60+mm)%(12*60));
        }
        sort(vec.begin(), vec.end());
        int tot = 0, c = 0;
        for (int i = 0; i < 3; i++) {
            int d1 = vec[i] - vec[(i+2)%3] + 12*60;
            int d2 = vec[(i+1)%3] - vec[i] + 12*60;
            d1 %= 12*60;
            d2 %= 12*60;
            if (d1 == d2) {
                c = vec[i];
                tot++;
            }
        }
        if (tot == 1) {
            printf("The correct time is %d:%0.2d\n", c/60 == 0 ? 12 : c/60, c%60);
        } else {
            printf("Look at the sun\n");
        }
    }
}

//
//  main.cpp
//  Uvalive5682.A-Class Statistics
//
//  Created by eycia on 13/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

vector<int> vec;

int main(int argc, const char * argv[]) {
    int t;
    scanf("%d", &t);
    for (int ff = 1; ff <= t; ff++) {
        vec.clear();
        int n, tmp;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &tmp);
            vec.push_back(tmp);
        }
        sort(vec.begin(), vec.end());
        printf("Class %d\n", ff);
        int mx = 0;
        for (int i = 1; i < vec.size(); i++) {
            if (vec[i] - vec[i-1] > mx) {
                mx = vec[i]-vec[i-1];
            }
        }
        printf("Max %d, Min %d, Largest gap %d\n", vec[vec.size()-1], vec[0], mx);
    }
}

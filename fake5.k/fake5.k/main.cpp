//
//  main.cpp
//  fake5.k
//
//  Created by eycia on 3/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

char ch[300];
map<char, int> mp;

int main(int argc, const char * argv[]) {
    for (char c = 'A'; c <= 'Z'; c++) {
        mp[c] = c-'A'+1;
    }
    while (gets(ch)) {
        int tot = 0;
        for (int i = 0; ch[i]; i++) {
            tot+=mp[ch[i]];
        }
        if (tot > 100) {
            puts("INVALID");
        } else {
            printf("%d\n", tot);
        }
    }
}

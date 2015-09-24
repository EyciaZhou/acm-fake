//
//  main.cpp
//  Vultures2.d
//
//  Created by eycia on 10/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;

char s[6000];

int main(int argc, const char * argv[]) {
    while (gets(s)) {
        int sl = strlen(s);
        //cout << sl << " " << ceil(sl/16.0) << endl;
        for (int r = 0; r < ceil(sl / 16.0); r++) {
            printf("%04d: ", r*10);
            for (int i = r*16; i < r*16+16; i++) {
                if (i >= sl) {
                    printf("  ");
                } else {
                    printf("%02x", s[i]);
                }
                if (i % 2 == 1) putchar(' ');
            }
            for (int i = r*16; i < min(sl, r*16+16); i++) {
                if (s[i] <= 'z' && s[i] >= 'a') {
                    putchar(s[i] - 'a' + 'A');
                } else if (s[i] <= 'Z' && s[i] >= 'A') {
                    putchar(s[i] - 'A' + 'a');
                } else {
                    putchar(s[i]);
                }
            }
            printf("\n");
        }
    }
}

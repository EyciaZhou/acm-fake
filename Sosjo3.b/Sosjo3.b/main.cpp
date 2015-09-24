//
//  main.cpp
//  Sosjo3.b
//
//  Created by eycia on 6/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <cstdio>
#include <cstring>

char key[1005], pa[100005];

int main(int argc, const char * argv[]) {
    while (gets(key)) {
        if (key[0] == '0') break;
        
        gets(pa);
        int lk = strlen(key), lp = strlen(pa);
        
        for (int i = 0; i < lp; i++) {
            putchar((key[i%lk]+pa[i]-'A'-'A'+1)%26+'A');
        }
        putchar('\n');
    }
}

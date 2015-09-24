//
//  main.cpp
//  Vultures.f
//
//  Created by eycia on 7/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int t, l, w, h;
    cin >> t;
    for (int ff = 1; ff <= t; ff++) {
        cin >> l >> w >> h;
        if (l <= 20 && w <= 20 && h <= 20) {
            cout << "Case " << ff << ": good" << endl;
        } else {
            cout << "Case " << ff << ": bad" << endl;
        }
    }
}

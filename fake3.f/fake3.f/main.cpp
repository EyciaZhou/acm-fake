//
//  main.cpp
//  fake3.f
//
//  Created by eycia on 30/7/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int t;
    long long a, b, c;
    cin >> t;
    while (t--) {
        cin >> a >> b >> c;
        cout << (b + b + (a-1) * c) * a / 2 << endl;
    }
}

//
//  main.cpp
//  cf.pi.a
//
//  Created by eycia on 6/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
using namespace std;

int st[100005];

int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> st[i];
    }
    cout << st[1]-st[0] << " " << st[n-1]-st[0] << endl;
    for (int i = 1; i < n-1; i++) {
        cout << min(st[i] - st[i-1], st[i+1] - st[i]) <<
        " " << max(st[i] - st[0], st[n-1]-st[i]) << endl;
    }
    cout << st[n-1] - st[n-2] << " " << st[n-1] - st[0] << endl;
}

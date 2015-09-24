//
//  main.cpp
//  cf.pi.b
//
//  Created by eycia on 6/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <set>
using namespace std;

set<int> ss;
int mx;

int main(int argc, const char * argv[]) {
    int n, nu;
    char o;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> o >> nu;
        if (o == '-') {
            if (ss.find(nu) == ss.end()) {
                mx++;
            } else {
                ss.erase(nu);
            }
        } else {
            ss.insert(nu);
            if (ss.size() > mx) {
                mx = ss.size();
            }
        }
    }
    cout << mx << endl;
}

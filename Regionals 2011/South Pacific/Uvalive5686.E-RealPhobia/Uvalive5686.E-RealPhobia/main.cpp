//
//  main.cpp
//  Uvalive5686.E-RealPhobia
//
//  Created by eycia on 13/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
using namespace std;

int ale, ari;
double mi, tar;

bool findle(int tle, int tri) {
    if (tle <= 0 || tri <= 0) return false;
    if (tle > tri) return false;
    double step = tle/(tri+0.0);
    if (step > tar) return false;
    
    if (step > mi) {
        mi = step;
        ale = tle;
        ari = tri;
        return findle(tle+1, tri);
    }
    
    if (findle(tle+1, tri)) {
        return true;
    }
    return findle(tle-1, tri-1);
}

bool findri(int tle, int tri) {
    if (tle <= 0 || tri <= 0) return false;
    if (tle > tri) return false;
    double step = tle/(tri+0.0);
    if (step < tar) return false;
    
    if (step < mi) {
        mi = step;
        ale = tle;
        ari = tri;
        return findri(tle-1, tri);
    }
    
    if (findle(tle-1, tri)) {
        return true;
    }
    return findle(tle+1, tri+1);
}

int main(int argc, const char * argv[]) {
    int t, le, ri;
    char o;
    cin >> t;
    while (t--) {
        cin >> le >> o >> ri;
        tar = le / (ri+0.0);
        ale = le-1;
        if (ale <= 0) ale++;
        ari = ri-1;
        mi = ale / (ari+0.0);
        findle(ale, ari);
        
        tar = le / (ri+0.0);
        ale = le-1;
        if (ale <= 0) ale++;
        ari = ri-1;
        mi = ale / (ari+0.0);
        findri(ale, ari);
        
        cout << ale << "/" << ari << endl;
    }
}

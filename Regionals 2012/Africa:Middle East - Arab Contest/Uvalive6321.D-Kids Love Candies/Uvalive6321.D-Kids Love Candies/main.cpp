//
//  main.cpp
//  fake4.d
//
//  Created by eycia on 31/7/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
	int t;
	cin >> t;
	while (t--) {
		int n, k, tot=0, tmp;
		cin >> n >> k;
		for (int i = 0; i < n; i++) {
			cin >> tmp;
			tot += tmp/k;
		}
		cout << tot << endl;
	}
}

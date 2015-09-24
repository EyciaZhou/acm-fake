//
//  main.cpp
//  fake4.i
//
//  Created by eycia on 31/7/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <set>
#include <cstring>
using namespace std;

int mp[105][105];
set<int> ss;

int sx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int sy[8] = {1, 0, -1, 1, -1, 1, 0, -1};

int main(int argc, const char * argv[]) {
	int t, n, m;
	cin >> t;
	while (t--) {
		ss.clear();
		cin >> n >> m;
		for (int i = 0; i < 105; i++) {
			for (int j = 0; j < 105; j++) {
				mp[i][j] = -1;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> mp[i][j];
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (mp[i][j] < 0) continue;
				int tot = 0;
				for (int k = 0; k < 8; k++) {
					if (mp[i+sx[k]][j+sy[k]] == mp[i][j]) tot++;
				}
				if (tot >= 1) {
					ss.insert(mp[i][j]);
				}
			}
		}
		cout << ss.size() << endl;
	}
}

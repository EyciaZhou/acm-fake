//
//  main.cpp
//  Sojos2.e
//
//  Created by eycia on 5/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

vector<int> xx, yy;

struct {
	int x0, x1, y0, y1;
} b[205];

int mp[205][205];
int mp2[205][205];

int main(int argc, const char * argv[]) {
	int n, w, h;
	while (cin >> n >> w >> h) {
		memset(mp, 0, sizeof(mp));
		xx.clear();
		yy.clear();
		for (int i = 0; i < n; i++) {
			cin >> b[i].x0 >> b[i].y0 >> b[i].x1 >> b[i].y1;
			xx.push_back(b[i].x0);
			xx.push_back(b[i].x1);
			yy.push_back(b[i].y0);
			yy.push_back(b[i].y1);
		}
		sort(xx.begin(), xx.end());
		sort(yy.begin(), yy.end());
		xx.erase(unique(xx.begin(), xx.end()), xx.end());
		yy.erase(unique(yy.begin(), yy.end()), yy.end());
		
		for (int i = 0; i < n; i++) {
			int xl = lower_bound(xx.begin(), xx.end(), b[i].x0) - xx.begin();
			int yl = lower_bound(yy.begin(), yy.end(), b[i].y0) - yy.begin();
			int xh = lower_bound(xx.begin(), xx.end(), b[i].x1) - xx.begin();
			int yh = lower_bound(yy.begin(), yy.end(), b[i].y1) - yy.begin();
			for (int i = xl; i < xh; i++) {
				for (int j = yl; j < yh; j++) {
					mp[i][j]++;
				}
			}
		}
		
		for (int i = 0; i < xx.size(); i++) {
			for (int j = 0; j < yy.size(); j++) {
				mp2[i][j] = (xx[i+1] - xx[i]) * (yy[j+1] - yy[j]);
			}
		}
		
		int mx = 0, s = 0, s2 = 0;
		for (int j = yy.size()-1; j >= 0; j--) {
			for (int i = 0; i < xx.size(); i++) {
				if (mp[i][j] > mx) {
					mx = mp[i][j];
				}
				if (mp[i][j] > 0) {
					s += mp2[i][j];
				}
			}
		}
		
		for (int j = yy.size()-1; j >= 0; j--) {
			for (int i = 0; i < xx.size(); i++) {
				if (mp[i][j] == mx) {
					mx = mp[i][j];
					s2 += mp2[i][j];
				}
			}
		}
		
		cout << w * h - s << " " << mx << " " << s2  << endl;
	}
}

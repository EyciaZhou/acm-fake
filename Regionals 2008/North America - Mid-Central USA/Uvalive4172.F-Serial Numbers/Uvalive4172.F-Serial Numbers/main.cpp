//
//  main.cpp
//  Sojos2.f
//
//  Created by eycia on 5/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
#include <tuple>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

#define int long long
char ss[1000];
int vv[1000];

vector<int> pos;
vector<tuple<int, int, char, int> > cache;

char title[100];
#undef int

int main(int argc, const char * argv[]) {
#define int long long
	int st, en, val;
	char sta;
	while (true) {
		cin.getline(title, 100);
		memset(ss, 0, sizeof(ss));
		memset(vv, 0, sizeof(vv));
		pos.clear();
		cache.clear();
		if (string(title) == "END") break;
		while (true) {
			cin >> st;
			if (st == 0) break;
			cin >> en >> sta >> val;
			cache.push_back(make_tuple(st, en+1, sta, val));
			pos.push_back(st);
			pos.push_back(en+1);
		}
		sort(pos.begin(), pos.end());
		pos.erase(unique(pos.begin(), pos.end()), pos.end());
		
		for (int i = 0; i < cache.size(); i++) {
			st = lower_bound(pos.begin(), pos.end(), get<0>(cache[i])) - pos.begin();
			en = lower_bound(pos.begin(), pos.end(), get<1>(cache[i])) - pos.begin();
			for (int j = st; j < en; j++) {
				ss[j] = get<2>(cache[i]);
				vv[j] = get<3>(cache[i]);
			}
		}
		cout << title << endl;
		if (pos.size() == 0) continue;
		st = pos[0];
		en = pos[1]-1;
		for (int i = 1; i < pos.size(); i++) {
			if (vv[i] == vv[i-1] && ss[i] == ss[i-1]) {
				en = pos[i+1]-1;
			} else {
				if (vv[i-1] != 0) cout << st << " " << en << " " << ss[i-1] << " " << vv[i-1] << endl;
				st = pos[i];
				en = pos[i+1]-1;
			}
		}
		cin.getline(title, 100);
	}
#undef int
}

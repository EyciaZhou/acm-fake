//
//  main.cpp
//  Sojos2.H
//
//  Created by eycia on 5/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

char tmp[90];

vector<int> ans;

int main(int argc, const char * argv[]) {
	while (true) {
		ans.clear();
		while (true) {
			gets(tmp);
			if (tmp[0] == '*') break;
			if (tmp[0] == '#') return 0;
			int sl = strlen(tmp), tot = 0;
			bool bl = false;
			for (int i = 0; i <= sl; i++) {
				if (tmp[i] == ' ') {
					if (!bl) bl = true;
					tot++;
				} else {
					if (bl) {
						bl = false;
						ans.push_back(tot);
						tot = 0;
					}
				}
			}
		}
		for (int i = 0; i < 5; i++) ans.push_back(1);
		int sl = ceil(ans.size() / 5.0)-1;
		for (int i = 0; i < sl; i++) {
			int a = 0;
			for (int j = 0; j < 5; j++) {
				a = a * 2 + (ans[i*5+j]+1)%2;
			}
			switch (a) {
				case 0:  a = ' '; break;
				case 27: a = '\''; break;
				case 28: a = ','; break;
				case 29: a = '-'; break;
				case 30: a = '.'; break;
				case 31: a = '?'; break;
				default: a = a + 'A' - 1; break;
			}
			putchar(a);
		}
		putchar('\n');
	}
}

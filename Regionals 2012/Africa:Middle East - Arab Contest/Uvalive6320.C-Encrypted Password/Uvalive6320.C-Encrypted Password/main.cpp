//
//  main.cpp
//  fake4.c
//
//  Created by eycia on 31/7/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char en[110000];
char ori[110000];

char mp[300];
int zero;

int main(int argc, const char * argv[]) {
	int t;
	bool flag;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", ori);
		scanf("%s", en);
		memset(mp, 0, sizeof(mp));
		zero = 0;
		flag = false;
		
		
		int lp = strlen(en), lo = strlen(ori);
		for (int i = 0; i < lp; i++) {
			if (mp[en[i]] == 0) {
				zero--;
			}
			mp[en[i]]++;
		}
		for (int i = 0; i < lp; i++) {
			if (mp[ori[i]] - 1 == 0) {
				zero++;
			}
			mp[ori[i]]--;
		}
		if (zero == 0) {
			flag = true;
		} else
			for (int i = lp; i < lo; i++) {
				
				if (mp[ori[i]] - 1 == 0) {
					zero++;
				}
				mp[ori[i]]--;
				
				if (mp[ori[i-lp]] == 0) {
					zero--;
				}
				mp[ori[i-lp]]++;
				
				if (zero == 0) {
					flag = true;
					//break;
				}
			}
		if (flag) {
			puts("YES");
		} else {
			puts("NO");
		}
	}
}

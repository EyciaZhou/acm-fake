//
//  main.cpp
//  Sosjo2.a
//
//  Created by eycia on 5/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>

char s[50];

int main(int argc, const char * argv[]) {
	while (true) {
		gets(s);
		if (s[0] == '#') {
			break;
		}
		
		int tot = 0;
		for (int i = 0; i < strlen(s); i++) {
			if (s[i] == '1') {
				tot++;
			}
			if (s[i] == '1' || s[i] == '0') {
				putchar(s[i]);
			}
		}
		if ((s[strlen(s) - 1] == 'e') ^ (tot % 2)) {
			printf("%d\n", 0);
		} else {
			printf("%d\n", 1);
		}
	}
}

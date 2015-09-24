//
//  main.cpp
//  fake4.h
//
//  Created by eycia on 2/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
using namespace std;

char tmps[200];

int f[305][305];
int g[305][305];

bool floyd(int n) {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (f[i][k] >= 0 && f[k][j] >= 0) {
					if (f[i][j] < 0 || f[i][j] > f[i][k] + f[k][j]) {
						if (g[i][j] < 0) {
							f[i][j] = f[i][k] + f[k][j];
						} else {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

void wk() {
	int n, n2;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%s", tmps);
		for (int j = 0; j < n; j++) {
			if (tmps[j] == '0') {
				f[i][j] = g[i][j] = 0;
			} else if (tmps[j] == '1') {
				f[i][j] = g[i][j] = 1;
			} else {
				f[i][j] = 1;
				g[i][j] = -1;
			}
		}
	}
	n2 = n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%s", tmps);
		for (int j = 0; j < n; j++) {
			if (tmps[j] == '0') {
				f[n2+i][n2+j] = g[n2+i][n2+j] = 0;
			} else if (tmps[j] == '1') {
				f[n2+i][n2+j] = g[n2+i][n2+j] = 1;
			} else {
				f[n2+i][n2+j] = 1;
				g[n2+i][n2+j] = -1;
			}
		}
	}
	
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < n; j++) {
			f[i][n2+j] = 1;
			g[i][n2+j] = -1;
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n2; j++) {
			f[n2+i][j] = 1;
			g[n2+i][j] = -1;
		}
	}
	n = n + n2;
	if (floyd(n)) {
		cout << "YES" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << f[i][j];
			}
			cout << endl;
		}
	} else {
		cout << "NO" << endl;
	}
}

int main(int argc, const char * argv[]) {
	int t;
	cin >> t;
	while (t--) {
		wk();
	}
}

/*
 YES
 01100
 10000
 10000
 00001
 00010
 
 011xx
 10xxx
 1x0xx
 xxx01
 xxx10
 */
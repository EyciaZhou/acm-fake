//
//  main.cpp
//  fake4.f
//
//  Created by eycia on 31/7/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

long long tot;
int ml = 9;
//bool v[15] = {false};
int v;
bool nl[15] = {false};

int c2[6][3] = {
	{1, 10, 4},
	{2, 11, 5},
	{3, 12, 6},
	{10, 1, 4},
	{11, 2, 8},
	{12, 3, 9}
};

int cc[34][3] = {
	{1, 3, 2},
	{1, 7, 4},
	{1, 10, 7},
	
	{1, 9, 5},
	
	{2, 8, 5},
	{2, 11, 8},
	
	{3, 1, 2},
	{3, 7, 5},
	{3, 9, 6},
	{3, 12, 9},
	
	{4, 6, 5},
	{4, 12, 8},
	{4, 10, 7},
	
	{5, 11, 8},
	
	{6, 4, 5},
	{6, 10, 8},
	{6, 12, 9},
	
	{7, 1, 4},
	{7, 3, 5},
	{7, 9, 8},
	
	{8, 2, 5},
	
	{9, 1, 5},
	{9, 3, 6},
	{9, 7, 8},
	
	{10, 1, 7},
	{10, 4, 7},
	{10, 12, 11},
	{10, 6, 8},
	
	{11, 5, 8},
	{11, 2, 5},
	
	{12, 3, 6},
	{12, 6, 9},
	{12, 10, 11},
	{12, 4, 8}
};

int mp[15][15];
int mp2[15][15];

inline int abs(int a) {
	if (a < 0) {
		return -a;
	}
	return a;
}

inline int dis(int a, int b) {
	if (a == 0) return 0;
	int x1 = (a-1) % 3;
	int y1 = (a-1) / 3;
	
	int x2 = (b-1) % 3;
	int y2 = (b-1) / 3;
	return abs(x1-x2) + abs(y1-y2);
}

long long mem[13][40][16385];
bool vv[13][40][16385];

long long mx = 0;

long long tt(int lst, long long ll) {
	if (vv[lst][ll][v]) return mem[lst][ll][v];
	if (ll > ml) return 0;
	if (ll == ml) {
		return 1;
	}
	
	long long tot = 0;
	for (int i = 1; i <= 12; i++) {
		if (v & (1 << (i))) continue;
		if (nl[i]) continue;
		if ((v & (1 << (mp[lst][i]))) != 0 &&
			(v & (1 << (mp2[lst][i]))) != 0) {
			v += (1 << i);
			tot += tt(i, ll+dis(lst, i));
			v -= (1 << i);
		}
	}
	vv[lst][ll][v] = true;
	mem[lst][ll][v] = tot;
	return tot;
}

int main(int argc, const char * argv[]) {
	int t, nln, xx, yy;
	scanf("%d", &t);
	memset(mp, 0, sizeof(mp));
	memset(mp2, 0, sizeof(mp2));
	for (int i = 0; i < 34; i++) {
		mp[cc[i][0]][cc[i][1]] = cc[i][2];
	}
	for (int i = 0; i < 6; i++) {
		mp2[c2[i][0]][c2[i][1]] = c2[i][2];
	}
	while (t--) {
		tot = 0;
		memset(nl, false, sizeof(nl));
		memset(vv, 0, sizeof(vv));
		v = 1;
		
		scanf("%d %d", &ml, &nln);
		for (int i = 0; i < nln; i++) {
			scanf("%d %d", &xx, &yy);
			nl[(yy-1)*3+xx] = true;
		}
		tot = tt(0, 0);
		if (tot == 0) {
			puts("BAD MEMORY");
		} else {
			printf("%lld\n", tot);
		}
	}
}
//4 6 30 144
/*
 1 34
 2 92
 3 338
 4 886
 5 2694
 6 6498
 7 17856
 10 187524
 15 4138408
 30 5550216
 37 11252
 38 1096
 */
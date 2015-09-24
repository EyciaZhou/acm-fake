//
//  main.cpp
//  fake4.e
//
//  Created by eycia on 31/7/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 731;
const int INF = 0x7fffffff;
int num_node;
#define o1 1
#define o2 30
#define o3 600

int map[N][N];
int pre[N];
int flow_in[N];
int start, en;
std::queue<int> q;

int find_one_bfs() {
	int i, t;
	while (!q.empty()) {
		q.pop();
	}
	memset(pre, -1, sizeof(pre));
	
	pre[start] = 0;
	flow_in[start] = INF;
	
	q.push(start);
	while (!q.empty()) {
		t = q.front();
		q.pop();
		
		if (t == en) {
			break;
		}
		
		for (i = 1; i <= num_node; i++) {
			if (pre[i] == -1 &&  map[t][i]) {
				if (flow_in[t] < map[t][i]) {
					flow_in[i] = flow_in[t];
				} else {
					flow_in[i] = map[t][i];
				}
				q.push(i);
				pre[i] = t;
			}
		}
	}
	if (pre[en] == -1) {
		return -1;
	} else{
		return flow_in[en];
	}
}

int lo;

int zdl() {
	int max_flow = 0;
	int cf_p;
	int now, prev;
	
	while ((cf_p = find_one_bfs()) != -1) {
		max_flow += cf_p;
		now = en;
		
		while (now != start) {
			prev = pre[now];
			map[prev][now] -= cf_p;
			map[now][prev] += cf_p;
			now = prev;
		}
	}
	int tot = 0;
	for (int i = 0; i < lo; i++) {
		if (map[o3+i][730] == 0) {
			tot++;
		}
	}
	return tot;
	return max_flow;
}

char st[105];
char tmp[105][10];
int vec[26];

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	//t = 1;
	while (t--) {
		scanf("%s", st);
		lo = strlen(st);
		memset(vec, 0, sizeof(vec));
		memset(map, 0, sizeof(map));
		for (int i = 0; i < lo; i++) {
			vec[st[i]-'a']++;
		}
		for (int i = 0; i < 26; i++) {
			map[0][o1+i] = vec[i];
		}
		for (int i = 0; i < lo; i++) {
			scanf("%s", tmp[i]);
			int l2 = strlen(tmp[i]);
			sort(tmp[i], tmp[i]+l2);
			for (int j = 0; j < l2; j++) {
				map[o1+tmp[i][j]-'a'][o2+i*5+j] = 1;
				map[o2+i*5+j][o3+i] = 1;
				map[o3+i][730] = 1;
			}
		}
		
		start = 0;
		en = 730;
		num_node = 731;
		int zd = zdl();
		
		if (zd != lo) {
			puts("NO SOLUTION");
			continue;
		}
		
		for (int i = 0; i < lo; i++) {
			int l2 = strlen(tmp[i]);
			
			for (int j = 0; j < l2; j++) {
				if (map[o1+tmp[i][j]-'a'][o2+i*5+j] == 0) {
					map[0][o1+tmp[i][j]-'a']++;
				}
			}
			
			for (int j = 0; j < l2; j++) {
				map[o1+tmp[i][j]-'a'][o2+i*5+j] = 0;
				map[o2+i*5+j][o3+i] = 0;
				map[o3+i][730] = 0;
			}
			
			for (int j = 0; j < l2; j++) {
				map[o1+tmp[i][j]-'a'][o2+i*5+j] = 1;
				map[o2+i*5+j][o3+i] = 1;
				map[o3+i][730] = 1;
				int z2 = zdl();
				if (z2 == zd) {
					putchar(tmp[i][j]);
					break;
				}
				map[o1+tmp[i][j]-'a'][o2+i*5+j] = 0;
				map[o2+i*5+j][o3+i] = 0;
				map[o3+i][730] = 0;
			}
		}
		puts("");
	}
}
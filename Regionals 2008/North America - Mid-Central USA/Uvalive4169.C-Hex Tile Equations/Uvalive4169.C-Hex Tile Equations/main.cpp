//
//  main.cpp
//  Sosjo2.c
//
//  Created by eycia on 5/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <cstdio>
using namespace std;

char mp[20][20];
bool v[20][20];
int pos;

char ans[500];
int hh, ll;

int sx[6] = {0, 0, -1, -1, 1, 1};
int sy[6] = {-2, 2, -1, 1, -1, 1};

inline bool dig(char c) {
	return c <= '9' && c >= '0';
}

bool cal() {
	//return true;
	ans[pos] = '=';
	int a[2] = {0, 0};
	stack<int> num;
	stack<char> smb;
	int i = 0, x = 0;
	for (int t = 0; t < 2; t++) {
		bool flag = true;
		while (flag) {
			if (!dig(ans[i])) {
				num.push(x);
				x = 0;
				if (num.size() >= 2) {
					int le = num.top();num.pop();
					int ri = num.top();num.pop();
					
					char sb = smb.top();smb.pop();
					//cout << ri << " " << le << " " << sb << endl;
					if (sb == '+') {
						num.push(le+ri);
					}
					if (sb == '-') {
						num.push(ri - le);
					}
					if (sb == '*') {
						num.push(ri * le);
					}
					if (sb == '/') {
						if (le == 0) return false;
						if (ri % le == 0) {
							num.push(ri / le);
						} else {
							return false;
						}
					}
				}
				smb.push(ans[i]);
			} else {
				x = x * 10 + ans[i] - '0';
			}
			if (ans[i] == '=') flag = false;
			i++;
		}
		a[t] = num.top();
		num.pop();
	}
	return a[0] == a[1];
}


void dfs(int ii, int jj, int le, int nn) {
	if (pos == le) {
		if (!dig(mp[ii][jj])) return;
		if (cal()) {
			for (int i = 0; i < pos; i++) {
				cout << ans[i];
			}
			cout << endl;
		}
		return ;
	}
	for (int i = 0; i < 6; i++) {
		if (ii + sx[i] >= 0 && jj + sy[i] >= 0 && mp[ii + sx[i]][jj + sy[i]] != ' ') {
			if (!v[ii + sx[i]][jj + sy[i]]) {
				if (dig(mp[ii + sx[i]][jj + sy[i]]) && mp[ii][jj] == '0') continue;
				if (!dig(mp[ii + sx[i]][jj + sy[i]]) && !dig(mp[ii][jj])) continue;
				if (dig(mp[ii + sx[i]][jj + sy[i]]) && nn == 2) continue;
				
				v[ii + sx[i]][jj + sy[i]] = true;
				ans[le] = mp[ii + sx[i]][jj + sy[i]];
				if (dig(mp[ii + sx[i]][jj + sy[i]])) {
					dfs(ii + sx[i], jj + sy[i], le+1, nn+1);
				} else {
					dfs(ii + sx[i], jj + sy[i], le+1, 0);
				}
				v[ii + sx[i]][jj + sy[i]] = false;
			}
		}
	}
}

int main(int argc, const char * argv[]) {
	while (cin >> hh >> ll) {
		memset(mp, ' ', sizeof(mp));
		memset(v, false, sizeof(v));
		pos = 0;
		for (int i = 0; i < hh; i++) {
			if (i % 2) {
				for (int j = 0; j <= ll*2; j+=2) {
					cin >> mp[i][j];
					pos++;
				}
			} else {
				for (int j = 1; j <= ll*2; j+=2) {
					cin >> mp[i][j];
					pos++;
				}
			}
		}
		
		for (int i = 0; i < hh; i++) {
			for (int j = 0; j <= ll*2; j++) {
				if (mp[i][j] != ' ' && mp[i][j] != '0' && dig(mp[i][j])) {
					v[i][j] = true;
					ans[0] = mp[i][j];
					dfs(i, j, 1, 1);
					v[i][j] = false;
				}
			}
		}
	}
}
/*
 5 2
 9 -
 * 2 =
 3 4
 + 0 3
 4 /
 */

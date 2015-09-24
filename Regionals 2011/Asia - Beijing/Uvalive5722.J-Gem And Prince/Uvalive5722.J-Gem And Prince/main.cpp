//
//  main.cpp
//  Uvalive5722.J-Gem And Prince
//
//  Created by eycia on 7/9/15.
//  Copyright (c) 2015 eycia. All rights reserved.
//

#include <set>
#include <map>
#include <list>
#include <tuple>
#include <ratio>
#include <cmath>
#include <queue>
#include <stack>
#include <deque>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, k;
long long mxans;

int cnt[10][10];

void fall_left(int (&cnt)[10][10]) {
	int l = 1;
	for (int j = 1; j <= m; j++) {
		int p = n;
		for (int i = n; i >= 1; i--) {
			if (cnt[i][j] != 0) {
				cnt[p--][l] = cnt[i][j];
			}
		}
		for (int i = p ; i >= 1; i--) {
			cnt[i][l] = 0;
		}
		if (p != n) {
			l++;
		}
	}
	for (int j = l; j <= m; j++) {
		for (int i = 1; i <= n; i++) {
			cnt[i][j] = 0;
		}
	}
}

void pr(int (&cnt)[10][10]) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			printf("%d	", cnt[i][j]);
		}
		puts("");
	}
	puts("");
}

int sx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int sy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int cc[10];

void dfs(int (&cnt)[10][10], long long sco) {
	int t2[10][10];
	bool v[10][10];
	vector<pair<int, int> > g;
	memset(v, false, sizeof(v));
	memset(t2, 0, sizeof(t2));
	g.clear();
	
	if (sco > mxans) {
		mxans = sco;
	}
	
	if (cnt[n][1] == 0) return;
	
	long long tot = 0;
	for (int i = 1; i <= k; i++) {
		if (cc[i] >= 3) {
			tot += cc[i]*cc[i];
		}
	}
	if (sco + tot <= mxans) {
		return;
	}
	
	queue<pair<int, int> > q;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (v[i][j] || cnt[i][j] == 0) continue;
			g.clear();
			q.push(make_pair(i, j));
			v[i][j] = true;
			while (!q.empty()) {
				int i = q.front().first, j = q.front().second;
				g.push_back(make_pair(i, j));
				q.pop();
				for (int k = 0; k < 8; k++) {
					if (!v[i+sx[k]][j+sy[k]] && cnt[i+sx[k]][j+sy[k]] == cnt[i][j]) {
						v[i+sx[k]][j+sy[k]] = true;
						q.push(make_pair(i+sx[k], j+sy[k]));
					}
				}
			}

			int co = cnt[i][j];
			long long gs = g.size();
				
			if (gs < 3) continue;
				
			for (int i = 0; i < gs; i++) {
				cnt[g[i].first][g[i].second] = 0;
			}

			for (int ii = 1; ii <= n; ii++) {
				for (int jj = 1; jj <= m; jj++) {
					t2[ii][jj] = cnt[ii][jj];
				}
			}
				
			fall_left(t2);
			cc[co] -= gs;
			dfs(t2, sco + gs*gs);
			cc[co] += gs;
				
			for (int i = 0; i < gs; i++) {
				cnt[g[i].first][g[i].second] = co;
			}
		}
	}
}

int main(int argc, const char * argv[]) {
	while (scanf("%d %d %d", &n, &m, &k) != EOF) {
		memset(cnt, 0, sizeof(cnt));
		memset(cc, 0, sizeof(cc));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", &cnt[i][j]);
				cc[cnt[i][j]]++;
			}
		}
		mxans = 0;
		fall_left(cnt);
		dfs(cnt, 0);
		printf("%lld\n", mxans);
	}
}

//
//  main.cpp
//  a7
//
//  Created by eycia on 14/9/15.
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

char st[40005];
char sr[40005];

struct cc {
	cc(char *c) : c(c) {}
	cc() : c(0) {}
	char *c;
};

vector<pair<cc, pair<int, int> > > ps;

//int n;
int mm;

bool operator< (const cc &l, const cc &r) {
	for (int i = 0; i < mm; i++) {
		if (l.c[i] < r.c[i]) {
			return false;
		} else if(l.c[i] > r.c[i]) {
			return true;
		}
	}
	return false;
}
#define N 40005
char s[N]; // N > 256
char s2[N];
int n, sa[N], height[N], ran[N], tmp[N], top[N];
void makesa(char *s){ // O(N * log N)
	int i, j, len, na;
	na=(n<256?256:n);
	memset(top, 0, na * sizeof(int));
	for(i=0;i<n;i++)top[ran[i]=s[i]&0xff]++;
	for(i=1;i<na;i++)top[i]+=top[i-1];
	for(i=0;i<n;i++)sa[--top[ran[i]]]=i;
	for(len=1;len<n;len<<=1){
		for (i = 0; i < n; i++) {
			j = sa[i] - len;
			if (j < 0) j += n;
			tmp[ top[ ran[j] ]++ ] = j;
		}
		sa[ tmp[ top[0] = 0 ] ] = j = 0;
		for (i = 1; i < n; i++) {
			if (ran[ tmp[i] ] != ran[ tmp[i-1] ] || ran[ tmp[i]+len ]!=ran[ tmp[i-1]+len ]) top[++j] = i;
			sa[ tmp[i] ] = j;
		}
		memcpy(ran, sa , n * sizeof(int));
		memcpy(sa , tmp, n * sizeof(int));
		if (j >= n - 1) break;
	}
}

void work() {
	int nn;
	ps.clear();
	scanf("%d", &nn);
	mm = nn;
	scanf("%s", s);
	
	for (int i = 0; i < nn; i++) {
		s[nn+i] = s[i];
	}
	
	n = nn+nn+1;
	
	s[nn+nn] = '\0';
	makesa(s);
	pair<cc, pair<int, int> > p1 = make_pair(s+sa[n-1], make_pair(sa[n-1], 0));
	
	for (int i = 0; i < nn+nn; i++) {
		s2[i] = s[nn+nn-1-i];
	}
	s2[nn+nn] = 'z';
	makesa(s2);
	pair<cc, pair<int, int> > p2;
	
	for (int i = n-1; i >= 0; i--) {
		if (sa[i] < nn) {
			p2 = make_pair(s2+sa[i], make_pair(nn-sa[i]-1, 1));
			break;
		}
	}
	
	if (p2 < p1) {
		swap(p1, p2);
	}
	
	
	printf("%d %d\n", p1.second.first+1, p1.second.second);
	
}
/*
 1
 7
 abcbeba
 */
int main(int argc, const char * argv[]) {
	//freopen("/Users/eycia/i", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--) {
		work();
	}
}

//
//  main.cpp
//  Sosjo.a
//
//  Created by eycia on 4/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <map>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

map<string, int> names;
map<string, int> types;

char name[100];
char typ[100];
vector<pair<int, int> > boys[4];
int sco, mem, m;
int cor[30][30];
int tt[4] = {4, 4, 2, 1};
bool v[30];

int ans;

void cal(int fz, int nu, int rank, int sco) {
    if (fz >= 4) {
        for (int i = 0; i < mem; i++) {
            for (int j = 0; j < i; j++) {
                if (cor[i][j] != 0 && v[i] && v[j]) {
                    sco += cor[i][j];
                }
            }
        }
        if (sco > ans) {/*
            for (int i = 0; i < mem; i++) {
                cout << i << " " << v[i] << endl;
            }
            cout << endl;*/
            ans = sco;
        }
        return;
    }
    if (tt[fz] == nu) return cal(fz+1, 0, 0, sco);

    for (int i = rank; i < boys[fz].size(); i++) {
        v[boys[fz][i].first] = true;
        cal(fz, nu+1, i+1, sco+boys[fz][i].second);
        v[boys[fz][i].first] = false;
    }
}

int main(int argc, const char * argv[]) {
    types["defender"] = 0;
    types["midfielder"] = 1;
    types["striker"] = 2;
    types["goalkeeper"] = 3;
    while (scanf("%s %d %s", name, &sco, typ) != EOF) {
        names.clear();
        for (int i = 0; i < 4; i++) {
            boys[i].clear();
        }
        mem = 0;
        memset(cor, 0, sizeof(cor));
        
        names[string(name)] = mem;
        boys[types[string(typ)]].push_back(make_pair(mem, sco));
        mem++;
        
        for (int i = 0; i < 22; i++) {
            scanf("%s %d %s", name, &sco, typ);
            names[string(name)] = mem;
            boys[types[string(typ)]].push_back(make_pair(mem, sco));
            mem++;
        }
        
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%s %s %d", name, typ, &sco);
            cor[names[string(name)]][names[string(typ)]] = sco;
            cor[names[string(typ)]][names[string(name)]] = sco;
        }
        
        //cal
        if (boys[0].size() < 4 || boys[1].size() < 4 || boys[2].size() < 2 || boys[3].size() < 1) {
            puts("impossible");
            continue;
        }
        
        ans = -0x7fffffff;
        cal(0, 0, 0, 0);
        cout << ans << endl;
    }
}

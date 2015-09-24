//
//  main.cpp
//  Sosjo3.j
//
//  Created by eycia on 6/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <stack>
using namespace std;

string op;

vector<pair<int, long long> > ops;
map<string, int> mp;

long long nu, ans;
bool succ;

stack<long long> stk;

long long inline abs2(long long a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

void prstk() {
    stack<long long> bak;
    while (!stk.empty()) {
        bak.push(stk.top());
        stk.pop();
    }
    while (!bak.empty()) {
        stk.push(bak.top());
        cout << bak.top() << " ";
        bak.pop();
    }
    cout << endl;
}

void mul(long long m) {
    long long tmp, t2;
    while (!stk.empty()) stk.pop();
    stk.push(m);

    for (int i = 0; i < ops.size(); i++) {
        //prstk();
        if (ops[i].first == 0) {
            stk.push(ops[i].second);
        } else  if (ops[i].first <= 3) {
            if (stk.size() < 1) {
                succ = false;
                return;
            }
            switch (ops[i].first) {
                case 1:
                    stk.pop();
                    break;
                case 2:
                    tmp = stk.top();
                    stk.pop();
                    stk.push(-tmp);
                    break;
                case 3:
                    tmp = stk.top();
                    stk.push(tmp);
                    break;
            }
        } else {
            
            if (stk.size() < 2) {
                succ = false;
                return;
            }
            tmp = stk.top();
            stk.pop();
            t2 = stk.top();
            stk.pop();
            switch (ops[i].first) {
                case 4:
                    stk.push(tmp);
                    stk.push(t2);
                    break;
                case 5:
                    if (abs2(tmp+t2) > 1000000000) {
                        succ =false;
                        return;
                    }
                    stk.push(t2+tmp);
                    break;
                case 6:
                    if (abs2(t2-tmp) > 1000000000) {
                        succ =false;
                        return;
                    }
                    stk.push(t2-tmp);
                    break;
                case 7:
                    if (abs2(t2*tmp) > 1000000000) {
                        succ =false;
                        return;
                    }
                    stk.push(t2*tmp);
                    break;
                case 8:
                    if (tmp == 0 || abs2(t2/tmp) > 1000000000) {
                        succ =false;
                        return;
                    }
                    stk.push(t2/tmp);
                    break;
                case 9:
                    if (tmp == 0 || abs2(t2%tmp) > 1000000000) {
                        succ =false;
                        return;
                    }
                    stk.push(t2%tmp);
                    break;
            }
        }
    }
    if (stk.size() == 1) {
        ans = stk.top();
        succ = true;
        return;
    }
    succ = false;
}

int main(int argc, const char * argv[]) {
    //freopen("/Users/eycia/a", "r", stdin);
    mp["POP"] = 1;
    mp["INV"] = 2;
    mp["DUP"] = 3;
    mp["SWP"] = 4;
    mp["ADD"] = 5;
    mp["SUB"] = 6;
    mp["MUL"] = 7;
    mp["DIV"] = 8;
    mp["MOD"] = 9;
    while (cin >> op) {
        if (op == "QUIT") break;
        ops.clear();
        if (op!="END") {
        do {
            if (op == "NUM") {
                cin >> nu;
                ops.push_back(make_pair(0, nu));
            } else {
                ops.push_back(make_pair(mp[op], 0));
            }
            cin >> op;
        } while (op != "END");
        }
        long long n, m;
        cin >> n;
        while (n--) {
            cin >> m;
            mul(m);
            if (succ) {
                cout << ans << endl;
            } else {
                cout << "ERROR" << endl;
            }
        }
        cout << endl;
    }
}
/*
NUM 1
NUM 2
NUM 0
NUM 3
NUM 0
NUM 4
NUM 0
ADD
INV
ADD
MUL
MOD
SWP
SUB
DIV
POP
END

NUM 3
DUP
MUL
NUM 15
SWP
MOD
*/
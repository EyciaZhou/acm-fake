//
//  main.cpp
//  Sojos2.d
//
//  Created by eycia on 5/8/15.
//  Copyright (c) 2015年 eycia. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;

int pe[30], ti[30], tr[30], trti[30], wai[30];
bool hvp[30];

int main(int argc, const char * argv[]) {
	int b, peo;
	while (cin >> b >> peo) {
		if (b == 0 && peo == 0) break;
		b = -b;
		memset(wai, 0, sizeof(wai));
		
		for (int i = 0; i < b; i++) {
			cin >> pe[i] >> ti[i];
			tr[i] = trti[i] = wai[i] = 0;
			hvp[i] = false;
		}
		wai[0] = peo;
		int time = 0;
		while (true) {
			for (int i = 0; i < b; i++) {
				if (hvp[i]) trti[i]++;
				if (trti[i] == ti[i]) {
					wai[i+1] += tr[i];
					trti[i] = 0;
					hvp[i] = false;
				}
				if (!hvp[i] && wai[i] > 0) {
					tr[i] = min(wai[i], pe[i]);
					wai[i] -= min(wai[i], pe[i]);
					hvp[i] = true;
				}
			}
			time++;
			if (wai[b] == peo) break;
		}
		cout << time-1 << endl;
	}
}

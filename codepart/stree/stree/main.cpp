#define typec int
const typec inf = 0x3f3f3f3f;

struct Steiner {
#define V 55
#define A 12
	int vis[V], id[A];
	typec d[V][V], dp[1<<A][V];
	typec d2[1<<A];
	
	void steiner(int n, int a) {
		int i, j, k, mx, mk, top = (1 << a);
		for (k = 0; k < n; k++)
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					if (d[i][j] > d[i][k] + d[k][j])
						d[i][j] = d[i][k] + d[k][j];
		
		for (i = 0; i < a; i++) {
			for (j = 0; j < n; j++)
				dp[1 << i][j] = d[j][id[i]];
		}
		for (i = 0; i < top; i++) {
			if ((i & (i-1)) == 0) continue;
			memset(vis, 0, sizeof(vis));
			for (k = 0; k < n; k++) {
				for(dp[i][k] = inf, j = (i - 1)&i ;j; j = (j - 1)&i)
					if (dp[i][k] > dp[j][k] + dp[i-j][k])
						dp[i][k] = dp[j][k] + dp[i-j][k];
			}
			for (j = 0; mx = inf, j < n; j++) {
				for (k = 0; k < n; k++)
					if (dp[i][k] <= mx && vis[k] == 0)
						mx = dp[i][mk=k];
				for (k = 0, vis[mk] = 1; k < n; k++)
					if (dp[i][mk] > dp[i][k] + d[k][mk])
						dp[i][mk] = dp[i][k] + d[k][mk];
			}
		}
	}
	
	bool ck(int k, int a) {
		int t1 = 0, t2 = 0;
		for (int i = 0; i < a/2; i++) {
			t1+=k%2;
			k/=2;
		}
		for (int i = 0; i < a/2; i++) {
			t2+=k%2;
			k/=2;
		}
		return t2 == t1;
	}
	
	int steiner2(int n, int a) {
		int S = (1 << a) - 1;
		
		for (int s = 0; s <= S; s++) {
			for (int i = 0; i < n; i++) {
				d2[s] = min(d2[s], dp[s][i]);
			}
		}
		
		for (int ll = 0; ll <= S; ll++) {
			for (int rr = 0; rr <= S; rr++) {
				if ((ll & rr) != 0) continue;
				
				if (!(ck(ll, a) && ck(rr, a))) continue;
				
				d2[ll|rr] = min(d2[ll|rr], d2[ll]+d2[rr]);
				
			}
		}
		return d2[S];
	}
} ss;
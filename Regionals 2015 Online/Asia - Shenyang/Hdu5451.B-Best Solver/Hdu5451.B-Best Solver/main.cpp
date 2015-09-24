#include <cstdio>

#define int long long
int exp(int base, int up, long long mod) {
	int res = 1;
	int tmp = base;
	while (up) {
		if (up & 1) {
			res = res*tmp%mod;
		}
		tmp = tmp*tmp%mod;
		up >>= 1;
	}
	return res;
}
#undef int

struct mat2x2 {
	int a, b;int c, d;
	
	mat2x2(int a, int b, int c, int d) : a(a), b(b), c(c), d(d) {};
};

int mod;

mat2x2 inline operator*(mat2x2 &l, mat2x2 &r) {
	return mat2x2((l.a*r.a%mod+l.b*r.c%mod)%mod, (l.a*r.b%mod+l.b*r.d%mod)%mod,
				  (l.a*r.c%mod+l.c*r.d%mod)%mod, (l.c*r.b%mod+l.d*r.d%mod)%mod);
}

mat2x2 one(1, 0, 0, 1);
mat2x2 f(10, -1, 1, 0);

mat2x2 ksm2(mat2x2 n, long long up) {
	mat2x2 res = one;
	mat2x2 tmp = n;
	while (up) {
		if (up&1) {
			res = res*tmp;
		}
		tmp = tmp*tmp;
		up >>= 1;
	}
	return res;
}

int work() {
	int k, m;
	scanf("%d %d", &k, &m);
	mod = m;
	int j = (m+1)*(m-1);
	long long cf = exp(2, k, j);
	mat2x2 a = ksm2(f, cf);
	
	int ans = (a.c*98 + a.d*10-1)%mod;
	while (ans < 0) ans+=mod;
	
	return ans;
}

int main(int argc, const char * argv[]) {
	int t;
	scanf("%d", &t);
	for (int ff = 1; ff <= t; ff++) {
		printf("Case #%d: %d\n", ff, work());
	}
}

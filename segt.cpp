#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define ls l, m, rt << 1
#define rs m + 1, r, rt << 1 | 1
const int maxn = 120000;

int sum[maxn<<2];
int col[maxn<<2];
bool hs[40];

void pushup(int rt) {
	sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}

void pushdown(int rt, int x) {
	if(col[rt]) {
		col[rt<<1] = col[rt];
		col[rt<<1|1] = col[rt];
		sum[rt<<1] = col[rt] * (x - (x >> 1));
		sum[rt<<1|1] = col[rt] * (x >> 1);
		col[rt] = 0;
	}
}

void build(int l, int r, int rt) {
	col[rt] = 0;
	if(l == r) {
		sum[rt] = 1;
		return;
	}
	int m = (l + r) >> 1;
	build(ls);
	build(rs);
	pushup(rt);
}

void update(int L, int R, int c, int l, int r, int rt) {
	if(c * (r - l + 1) == sum[rt])
		return;
	if(L <= l && R >= r) {
		col[rt] = c;
		sum[rt] = c * (r - l + 1);
		return;
	}
	int m = (l + r) >> 1;
	pushdown(rt, r - l + 1);
	if(L <= m)
		update(L, R, c, ls);
	if(R > m)
		update(L, R, c, rs);
	sum[rt] = 0;
}

void query(int L, int R, int l, int r, int rt) {
	if(sum[rt] > 0) {
		hs[sum[rt] / (r - l + 1)] = true;
		return;
	}
	int m = (l + r) >> 1;
	if(L <= m) 
		query(L, R, ls);
	if(R > m)
		query(L, R, rs);
}

int main() {
	int l, t, o;
	while(scanf("%d%d%d", &l, &t, &o) == 3) {
		build(1, l, 1);
		char op[3];
		for(int i = 0; i < o; i ++) {
			scanf("%s", op);
			if(op[0] == 'C') {
				int x, y, z;
				scanf("%d%d%d", &x, &y, &z);
				update(x, y, z, 1, l, 1);
			}
			else {
				int x, y;
				scanf("%d%d", &x, &y);
				memset(hs, false, sizeof(hs));
				query(x, y, 1, l, 1);
				int ans = 0;
				for(int j = 1; j <= t; j ++)
					if(hs[j])
						ans ++;
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}
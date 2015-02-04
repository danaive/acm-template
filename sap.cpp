#include <bits/stdc++.h>
using namespace std;
const int maxint = 0x7f7f7f7f;
const int maxn = 2000;

bool chk_min(int &a, int b) {
	return a > b? a = b, true: false;
}

struct SAP {

	struct Edge {
		int u, v, cap, cost;
	};


	int n, s, t;
	int dis[maxn], pre[maxn];
	vector<int> g[maxn];
	vector<Edge> e;
	
	void init(int x) {
		n = x;
		s = 0;
		t = n - 1;
		for(int i = 0; i < n; i ++)
			g[i].clear();
		e.clear();
	}

	void add(int u, int v, int cap, int cost) {
		Edge e1 = {u, v, cap, cost};
		Edge e2 = {v, u, 0, -cost};
		g[u].push_back((int)e.size());
		e.push_back(e1);
		g[v].push_back((int)e.size());
		e.push_back(e2);
	}

	bool spfa() {
		bool vst[maxn];
		memset(vst, false, sizeof vst);
		memset(pre, -1, sizeof pre);
		memset(dis, 127, sizeof dis);
		queue<int> q;
		dis[s] = 0;
		vst[s] = true;
		q.push(s);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int i = 0; i < (int)g[u].size(); i ++) {
				int id = g[u][i];
				int v = e[id].v;
				if(e[id].cap && chk_min(dis[v], dis[u] + e[id].cost)) {
					pre[v] = id;
					if(!vst[v]) {
						vst[v] = true;
						q.push(v);
					}
				}
			}
		}
		return dis[t] < maxint;
	}

	pair<int, int> work() {
		int maxflow = 0;
		int mincost = 0;
		while(spfa()) {
			int minflow = maxint;
			for(int i = pre[t]; i != -1; i = pre[e[i].u]) 
				chk_min(minflow, e[i].cap);
			for(int i = pre[t]; i != -1; i = pre[e[i].u]) {
				e[i].cap -= minflow;
				e[i^i].cap += minflow;
			}
			maxflow += minflow;
			mincost += minflow * dis[t];
		}
		return make_pair(maxflow, mincost);
	}
}sap;

int main() {
	return 0;
}
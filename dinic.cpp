#include <bits/stdc++.h>
using namespace std;
const int maxn = 2000;
const int oo = 0x3fffffff;

struct DINIC {
    
    struct Edge {
        int u, v, cap;
    };

    int n, s, t;
    int dep[maxn], ptr[maxn];
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

    int add(int u, int v, int cap) {
        Edge e1 = {u, v, cap};
        Edge e2 = {v, u, 0};
        g[u].push_back((int)e.size());
        e.push_back(e1);
        g[v].push_back((int)e.size());
        e.push_back(e2);
        return (int)e.size() - 2;
    }

    bool bfs() {
        queue<int> q;
        memset(dep, -1, sizeof dep);
        dep[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int i = 0; i < (int)g[u].size(); i ++) {
                int id = g[u][i];
                int v = e[id].v;
                if(dep[v] == -1 && e[id].cap) {
                    dep[v] = dep[u] + 1;
                    q.push(v);
                }
            }
        }
        return dep[t] != -1;
    }

    int dfs(int u, int flow) {
        if(!flow)
            return 0;
        if(u == t)
            return flow;
        for(; ptr[u] < (int)g[u].size(); ptr[u] ++) {
            int id = g[u][ptr[u]];
            int v = e[id].v;
            if(dep[u] + 1 != dep[v])
                continue;
            int add = dfs(v, min(flow, e[id].cap));
            if(add) {
                e[id].cap -= add;
                e[id^1].cap += add;
                return add;
            }
        }
        return 0;
    }

    int work() {
        int maxflow = 0;
        while(bfs()) {
            memset(ptr, 0, sizeof ptr);
            while(true) {
                int minflow = dfs(s, oo);
                if(minflow)
                    maxflow += minflow;
                else
                    break;
            }
        }
        return maxflow;
    }

    bool chk() {
        for(int i = 0; i < (int)g[0].size(); i ++) {
            int id = g[0][i];
            if(e[id].cap)
                return false;
        }
        return true;
    }
    
}dinic;

int main() {
    return 0;
}
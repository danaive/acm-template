//author: Jne
//2013-05-15-09.32.14
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <list>
#define out(v) cout << #v << ":" << (v) << endl
#define flin freopen("in.txt","r",stdin)
#define flout freopen("out.txt","w",stdout)

using namespace std;
typedef long long lint;
const int inf = 1e9 + 7;
const double eps = 1e-8;
inline int sgn(const double x) {return (x > eps) - (x < -eps);}
template <class T> bool get_max(T &a, const T b) {return a < b ? a = b, true : false;}
template <class T> bool get_min(T &a, const T b) {return a > b ? a = b, true : false;}

struct Edge
{
    int u, v, cap;
};
int dep[1100], ptr[1100], n, s, t;
vector<Edge> e;
vector<int> g[1100];

inline void init()
{
    for(int i = 0; i < n; i ++)
        g[i].clear();
    e.clear();
}

inline void add_edge(int u, int v, int cap)
{
    Edge e1 = {u, v, cap};
    Edge e2 = {v, u, cap};
    g[u].push_back(e.size());
    e.push_back(e1);
    g[v].push_back(e.size());
    e.push_back(e2);
}

bool bfs()
{
    queue<int> q;
    memset(dep, -1, sizeof(dep));
    dep[s] = 0;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i = 0; i < (int)g[u].size(); i ++)
        {
            int id = g[u][i];
            int v = e[id].v;
            if(dep[v] == -1 && e[id].cap)
            {
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }
    //for(int i = 0; i < n; i ++)
    //    printf("dep %d : %d\n",i,dep[i]);
    return dep[t] != -1;
}

int dfs(int u, int flow)
{
    if(!flow) return 0;
    if(u == t) return flow;
    for(; ptr[u] < (int)g[u].size(); ptr[u] ++)
    {

        int id = g[u][ptr[u]];
        int v = e[id].v;
        if(dep[u] + 1 != dep[v])
            continue;
        /*if(flow)
        {
            out(u);
            out(v);
            out(flow);
            getchar();
        }*/
        int add = dfs(v, min(flow, e[id].cap));
        if(add)
        {
            e[id].cap -= add;
            e[id^1].cap += add;
            return add;
        }
    }
    return 0;
}

int dinic()
{
    int maxflow = 0;
    while(bfs())
    {
        memset(ptr, 0, sizeof(ptr));
        while(true)
        {
            int minflow = dfs(s, inf);
            if(minflow)
                maxflow += minflow;
            else break;
        }
    }
    return maxflow;
}

int main()
{
    int T, ca = 0;
    scanf("%d",&T);
    while(T --)
    {
        int m;
        scanf("%d%d%d%d",&n,&s,&t,&m);
        s --;
        t --;
        init();
        for(int i = 0; i < m; i ++)
        {
            int u, v, cap;
            scanf("%d%d%d",&u,&v,&cap);
            u --;
            v --;
            add_edge(u, v, cap);
            //add_edge(v, u, cap);
        }
        printf("Case %d: %d\n",++ca,dinic());
    }
    return 0;
}

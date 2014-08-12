//author: Jne
//2013-05-15-11.17.05
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

int n, s, t, dis[200], pre[200];
struct Edge
{
    int u, v, cap, cost;
};
vector<int> g[200];
vector<Edge> e;

inline void init()
{
    for(int i = 0; i < n; i ++)
        g[i].clear();
    e.clear();
}

inline void add_edge(int u, int v, int cap, int cost)
{
    Edge e1 = {u, v, cap, cost};
    Edge e2 = {v, u, 0, -cost};
    g[u].push_back(e.size());
    e.push_back(e1);
    g[v].push_back(e.size());
    e.push_back(e2);
}

bool spfa()
{
    bool inq[200];
    for(int i = 0; i < n; i ++)
    {
        pre[i] = -1;
        dis[i] = inf;
        inq[i] = false;
    }
    queue<int> q;
    dis[s] = 0;
    inq[s] = true;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for(int i = 0; i < (int)g[u].size(); i ++)
        {
            int id = g[u][i];
            int v = e[id].v;
            if(e[id].cap && get_min(dis[v], dis[u] + e[id].cost))
            {
                //out(u);
                //out(v);
                //out(dis[v]);
                pre[v] = id;
                if(!inq[v])
                {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
    //puts("");
    //out(dis[t]);
    return dis[t] != inf;
}

pair<int, int> mcmf()
{
    int maxflow = 0;
    int mincost = 0;
    while(spfa())
    {
        int minflow = inf;
        for(int i = pre[t]; i != -1; i = pre[e[i].u])
        {
            //out(e[i].v);
            //out(e[i].u);
            get_min(minflow, e[i].cap);
        }
        for(int i = pre[t]; i != -1; i = pre[e[i].u])
        {
            e[i].cap -= minflow;
            e[i^1].cap += minflow;
        }
        maxflow += minflow;
        mincost += minflow * dis[t];
        //out(mincost);
    }
    return make_pair(mincost, maxflow);
}

int main()
{
    int T, ca = 0;
    scanf("%d",&T);
    while(T --)
    {
        int nn, k, g;
        scanf("%d%d%d",&nn,&k,&g);
        int a[100], b[100];
        for(int i = 1; i <= nn; i ++)
            scanf("%d",&a[i]);
        for(int i = 1; i <= nn; i ++)
            scanf("%d",&b[i]);
        n = 2 * nn + 2;
        s = 0; t = n - 1;
        init();
        for(int i = 1; i <= nn; i ++)
        {
            add_edge(s, i, 1, 0);
            add_edge(i + nn, t, 1, 0);
        }
        for(int i = 1; i <= nn; i ++)
            for(int j = 1; j <= nn; j ++)
            if(a[i] < b[j])
            {
                int cost = (b[j] - a[i] - k) * (b[j] - a[i] - k);
                get_min(cost, g);
                add_edge(i, j + nn, 1, cost);
            }
        pair<int, int> ans = mcmf();
        if(ans.second < nn)
        {
            printf("Case %d: impossible\n",++ca);
            continue;
        }
        printf("Case %d: %d ",++ca,ans.first);
        init();
        for(int i = 1; i <= nn; i ++)
        {
            add_edge(s, i, 1, 0);
            add_edge(i + nn, t, 1, 0);
        }
        for(int i = 1; i <= nn; i ++)
            for(int j = 1; j <= nn; j ++)
            if(a[i] < b[j])
            {
                int cost = (b[j] - a[i] - k) * (b[j] - a[i] - k);
                get_min(cost, g);
                add_edge(i, j + nn, 1, -cost);
            }
        printf("%d\n",-mcmf().first);
    }
    return 0;
}

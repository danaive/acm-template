//author: Jne
//2013-07-18-12.15.31
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
#define pb push_back
#define PI acos(-1.0)
using namespace std;
typedef long long lint;
const int inf = 1e9 + 7;
const double eps = 1e-8;
inline int sgn(const double x) {return (x > eps) - (x < -eps);}
template <class T> bool get_max(T &a, const T b) {return a < b ? a = b, true : false;}
template <class T> bool get_min(T &a, const T b) {return a > b ? a = b, true : false;}
template <class T> void _swap(T &a, T &b) {T t = a; a = b; b = t;}


struct pnt{double x, y;}p[1000];
struct vct{double x, y;};
struct seg{pnt s, t; double a, b, c;};
const pnt o = {0.0, 0.0};
vct operator - (pnt s, pnt t)           //s->t向量
{
    vct res = {t.x - s.x, t.y - s.y};
    return res;
}

seg operator ^ (pnt s, pnt t)           //s->t线段 ^优先级低 使用是加括号
{
    double a = s.y - t.y;
    double b = t.x - s.x;
    double c = -(a * s.x + b * s.y);
    seg res = {s, t, a, b, c};
    return res;
}

double operator * (vct a, vct b)        //向量叉积
{
    return a.x * b.y - a.y * b.x;
}

double operator ^ (vct a, vct b)        //向量点积
{
    return a.x * b.x + a.y * b.y;
}

double dis(pnt a, pnt b)                //点距离
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double dis(pnt a, seg b)                //点到线段距离
{
    double s = (b.t - b.s) * (a - b.s);
    if(((b.t - b.s) ^ (a - b.s)) > -eps && ((b.s - b.t) ^ (a - b.t)) > -eps)
        return s / dis(b.s, b.t);
    return min(dis(a, b.s), dis(a, b.t));
}

double getS(pnt *p, int n)              //多边形面积 逆时针排序
{
    double ans = 0.0;
    p[n] = p[0];
    for(int i = 0; i < n; i ++)
        ans += (p[i] - o) * (p[i+1] - o);
    return ans / 2;
}

bool isIntersect(seg a, seg b)          //判断线段是否相交
{
    if(max(a.s.x, a.t.x) < min(b.s.x, b.t.x) - eps ||
       max(a.s.y, a.t.y) < min(b.s.y, b.t.y) - eps ||
       max(b.s.x, b.t.x) < min(a.s.x, a.t.x) - eps ||
       max(b.s.y, b.t.y) < min(a.s.y, a.t.y) - eps)
        return false;
    if(((a.t - a.s) * (b.t - a.s)) * ((a.t - a.s) * (b.s - a.s)) > eps ||
       ((b.t - b.s) * (a.t - b.s)) * ((b.t - b.s) * (a.s - b.s)) > eps)
        return false;
    return true;
}

pnt intersect(seg s1, seg s2)           //求线段交点 无交点则延长相交 注意共线情况
{
    pnt p1 = s1.s;
    pnt p2 = s1.t;
    pnt p3 = s2.s;
    pnt p4 = s2.t;
    double x = (p3.x - p4.x) * ((p1 - o) * (p2 - o)) - (p1.x - p2.x) * ((p3 - o) * (p4 - o));
    double y = (p3.y - p4.y) * ((p1 - o) * (p2 - o)) - (p1.y - p2.y) * ((p3 - o) * (p4 - o));
    double t = (p2 - p1) * (p4 - p3);
    pnt res = {x / t, y / t};
    return res;
}

seg shift(seg t, double m)              //线段向多边形内侧平移距离m 用得不多
{
    double l = dis(t.s, t.t);
    double dy = (t.t.x - t.s.x) * m / l;
    double dx = (t.t.y - t.s.y) * m / l;
    seg res;
    res.s.x = t.s.x - dx;
    res.t.x = t.t.x - dx;
    res.s.y = t.s.y + dy;
    res.t.y = t.t.y + dy;
    res = res.s ^ res.t;
    return res;
}

int cut(seg t, int cnt, pnt *p, pnt *q) //半平面交 用得很多
{
    int cur = 0;
    for(int i = 1; i <= cnt; i ++)
    {
        if(t.a * p[i].x + t.b * p[i].y + t.c > -eps)
            q[++cur] = p[i];
        else
        {
            if(t.a * p[i-1].x + t.b * p[i-1].y + t.c > eps)
                q[++cur] = intersect(t, p[i-1] ^ p[i]);
            if(t.a * p[i+1].x + t.b * p[i+1].y + t.c > eps)
                q[++cur] = intersect(t, p[i+1] ^ p[i]);
        }
    }
    cnt = cur;
    for(int i = 1; i <= cnt; i ++)
        p[i] = q[i];
    p[0] = p[cnt];
    p[cnt+1] = p[1];
    return cnt;
}

bool cmp(pnt a, pnt b)              //逆时针极角排序 p[0]为左下方点
{
    if(sgn((a - p[0]) * (b - p[0])) == 1)
        return true;
    if(!sgn((a - p[0]) * (b - p[0])) && dis(a, p[0]) < dis(b, p[0]))
        return true;
    return false;
}

int graham(int n, pnt *p, pnt *sk)  //凸包  返回凸包上点个数
{
    for(int i = 1; i < n; i ++)
        if(p[0].y > p[i].y || (p[0].y == p[i].y && p[0].x > p[i].x))
        {
            pnt tmp = p[0];
            p[0] = p[i];
            p[i] = tmp;
        }
    sort(p + 1, p + n, cmp);
    for(int i = 0; i < 3; i ++)
        sk[i] = p[i];
    int tp = 2;
    for(int i = 3; i < n; i ++)
    {
        while((sk[tp] - sk[tp-1]) * (p[i] - sk[tp-1]) < 0)
            tp --;
        sk[++tp] = p[i];
    }
    return tp + 1;
}



int main()
{

    return 0;
}

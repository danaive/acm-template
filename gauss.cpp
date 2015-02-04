#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 50;

int a[N][N];
int x[N];
bool fx[N];

int gcd(int a, int b) {
    if(a % b == 0)
        return b;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int gauss(int e, int v) {
    memset(x, 0, sizeof x);
    int k, col;
    for(k = 0, col = 0; k < e && col < v; k ++, col ++) {
        int mxr = k;
        for(int i = k + 1; i < e; i ++)
            if(abs(a[i][col]) > abs(a[mxr][col]))
                mxr = i;
        for(int j = k; j <= v; j ++)
            swap(a[k][j], a[mxr][j]);
        if(!a[k][col]) {
            k --;
            continue;
        }
        for(int i = k + 1; i < e; i ++) {
            if(a[i][col]) {
                int LCM = lcm(abs(a[i][col]), abs(a[k][col]));
                int ta = LCM / abs(a[i][col]);
                int tb = LCM / abs(a[k][col]);
                if(a[i][col] * a[k][col] < 0)
                    tb = -tb;
                for(int j = col; j <= v; j ++)
                    a[i][j] = a[i][j] * ta - a[k][j] * tb;
            }
        }
    }
    for(int i = k; i < e; i ++)
        if(a[i][col])
            return -1;
    if(k < v) {
        memset(fx, true, sizeof fx);
        for(int i = k - 1; i >= 0; i --) {
            int fn = 0;
            int fid;
            for(int j = 0; j < v; j ++)
                if(a[i][j] && fx[j]) {
                    fn ++;
                    fid = j;
                }
            if(fn > 1)
                continue;
            int tmp = a[i][v];
            for(int j = 0; j < v; j ++)
                if(a[i][j] && j != fid)
                    tmp -= a[i][j] * x[j];
            x[fid] = tmp / a[i][fid];
            fx[fid] = false;
        }
        return v - k;
    }
    for(int i = v - 1; i >= 0; i --) {
        int tmp = a[i][v];
        for(int j = i + 1; j < v; j ++)
            if(a[i][j])
                tmp -= a[i][j] * x[j];
        if(tmp % a[i][i])
            return -2;
        x[i] = tmp / a[i][i];
    }
    return 0;
}

int main() {
    return 0;
}
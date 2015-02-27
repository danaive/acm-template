#include <bits/stdc++.h>
using namespace std;

const int maxn = 1100000;
char s[maxn];
char ma[maxn];
int mp[maxn];

void manacher(int len) {
    ma[0] = '$';
    ma[1] = '*';
    int n = 2;
    for(int i = 0; i < len; i ++) {
        ma[n++] = s[i];
        ma[n++] = '*';
    }
    ma[n] = '\0';
    int mx = 0;
    int id = 0;
    for(int i = 0; i < n; i ++) {
        mp[i] = mx > i? min(mp[2*id-i], mx - i): 1;
        while(ma[i+mp[i]] == ma[i-mp[i]])
            mp[i] ++;
        if(i + mp[i] > mx) {
            mx = i + mp[i];
            id = i;
        }
    }
}

int main() {
    while(scanf("%s", s) == 1) {
        int len = strlen(s);
        manacher(len);
        int ans = 0;
        for(int i = 0; i < 2 * len + 2; i ++)
            ans = max(ans, mp[i] - 1);
        printf("%d\n", ans);
    }
    return 0;
}

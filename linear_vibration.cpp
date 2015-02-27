#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
lint a[10000];
void get_rev(int p) {
    a[1] = 1;
    for(int i = 2; i < p; i ++) {
        lint t = p / i;
        lint k = p % i;
        a[i] = i * t * t % p * a[k] % p * a[k] % p;
        cout << i << " " << a[i] << endl;
    }
}

int main() {
    get_rev(17);
    return 0;
}

#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9+7;

long long exp(int a, int b) {
    if(b == 0) return 1;
    if(b == 1) return a;

    long long res = 1;
    if(b%2 == 0) {
        auto temp = exp(a, b/2);
        res = temp * temp;
        res %= MOD;
    }
    else {
        auto temp = exp(a, b-1);
        res = temp * a;
        res %= MOD;
    }
    return res;
}

void solve() {
    int n;
    cin >> n;

    if(n%2 == 1) {
        cout << 0 << endl;
        return;
    }
    n/=2;
    long long fac[2*n+1];
    fac[0] = 1;
    for(int i = 1; i<=2*n; ++i) {
        fac[i] = fac[i-1] * i;
        fac[i] %= MOD;
    }

    long long res = fac[2*n];
    res *= exp(fac[n], MOD-2);
    res %= MOD;
    res *= exp(fac[n], MOD-2);
    res %= MOD;
    res *= exp(n+1, MOD-2);
    res %= MOD;
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
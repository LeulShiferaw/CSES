#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

void solve()
{
    int n;
    cin >> n;

    vector<ll> a(n);
    for(int i = 0; i<n; ++i) cin >> a[i];

    vector<ll> pmod(n, 0);
    ll curr_sum = 0;
    pmod[0] = 1;
    for(int i= 0; i<n; ++i)
    {
        curr_sum += a[i];
        pmod[((curr_sum % n) + n) % n]++;
    }

    ll res = 0;
    for(auto &val : pmod)
    {
        res += (val * (val-1)) / 2;
    }
    cout << res << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

void solve()
{
    int n, x;
    cin >> n >> x;

    vll a(n);
    for(int i = 0; i<n; ++i) cin >> a[i];

    ll res = 0;
    ll curr = a[0];
    int l = 0, r = 0;
    while(true)
    {
        if(curr == x)
        {
            ++res;
            ++r;
            if(r >= a.size()) break;
            curr += a[r];
        }
        else if(curr < x)
        {
            ++r;
            if(r >= a.size()) break;
            curr += a[r];
        }
        else if(l == r){
            ++l, ++r;
            if(l >= a.size()) break;
            curr = a[l];
        }
        else {
            curr -= a[l];
            ++l;
            if(l > r || l >= a.size()) break;
        }
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
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using indexed_set =  tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

const int MOD = (int)1e9 + 7;

/*
    For each of the values you know the dp for <=j for the current j
    Thererfore just use that
*/

void solve()
{
    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for(int i = 0; i<n; ++i) {
        cin >> c[i];
    }

    sort(c.begin(), c.end());
    vector<int> dp(x+1, 0);

    dp[0] = 1;
    for(int j = 0; j<n; ++j)
    {
        for(int i = c[j]; i<=x; ++i)
        {
            dp[i] += dp[i-c[j]];
            dp[i] %= MOD;
        }
    }
    cout << dp[x] << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
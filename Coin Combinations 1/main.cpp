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

const int MOD = 1000'000'000 + 7;

void solve()
{
    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for(int i = 0; i<n; ++i) cin >> c[i];

    sort(c.begin(), c.end());

    int dp[x+1];
    dp[0] = 1;
    for(int i = 1; i<=x; ++i)
    {
        int res = 0;
        for(const int &coin : c)
        {
            if(coin > i) break;
            res += dp[i-coin];
            res %= MOD;
        }
        dp[i] = res;
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
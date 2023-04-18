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

void solve()
{
    int n, x;
    cin >> n >> x;

    vector<int> coins(n);
    for(int i = 0; i<n; ++i) cin >> coins[i];

    sort(coins.begin(), coins.end());

    int dp[x+1];
    dp[0] = 0;
    for(int i = 1; i<=x; ++i)
    {
        int res = x+1;
        for(const auto &c : coins)
        {
            if(c > i) break;
            if(dp[i-c] == -1) continue;
            res = min(res, 1+dp[i-c]);
        }
        dp[i] = (res == (x+1)) ? -1 : res;
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
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for(int i = a; i<b; i++)
#define rREP(i, b, a) for(int i = b; i>=a; i--)

using indexed_set =  tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

/*
    In order for it to work on PC you need to use multidimensional pointers
    Just calculate dp[i][j] what would be the best for the person that goes first
    It doesn't matter if that is the second player or the first player
    The second players value can be found by subtracting from sum[i][j]
    Therefore, dp[i][j] = max(x[i] + sum[i+1][j] - dp[i+1][j], x[j] + sum[i][j-1] - dp[i][j-1])
    This is basically the same as saying make the first move at x[i] and get your result because you go second in the next one
    for that you just use the forumla mentioned before.
*/

ll rangeSum(ll sum[], int i, int j)
{
    if(i == 0) return sum[j];
    return sum[j] - sum[i-1];
}

void solve()
{
    int n;
    cin >> n;

    vector<ll> x(n);
    for(int i = 0; i<n; ++i) {
        cin >> x[i];
    }

    ll sum[n];
    sum[0] = x[0];
    for(int i=1; i<n; ++i) sum[i] = sum[i-1] + x[i];

    ll **dp;
    dp = new ll*[5000+1];
    for(int i = 0; i<=n; ++i)
        dp[i] = new ll[5000+1];
    
    rREP(i, n-1, 0) {
        REP(j, i, n) {
            if(i == j) {
                dp[i][j] = x[i];
                continue;
            }

            dp[i][j] = max(x[i] + rangeSum(sum, i+1, j) - dp[i+1][j], x[j] + rangeSum(sum, i, j-1) - dp[i][j-1]);
        }
    }
    cout << dp[0][n-1] << endl;

    for(int i = 0; i<=n; ++i)
        delete []dp[i];
    delete []dp;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
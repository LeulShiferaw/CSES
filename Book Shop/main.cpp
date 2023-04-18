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

/*
    Just reverse loops. By making j first and i next.
    Make sure to do from x to 1 b/c otherwise the new data will overwrite the new values.
    Think of it like this calculate for each price and prior successively.
*/

void solve()
{
    int n, x;
    cin >> n >> x;

    vector<int> h(n), s(n);
    for(int i=0; i<n; ++i) cin >> h[i];
    for(int i=0; i<n; ++i) cin >> s[i];

    vector<int> dp(x+1, 0);
    for(int j = 0; j<n; ++j)
    {
        for(int i = x; i>=h[j]; --i)
        {
            dp[i] = max(dp[i], dp[i-h[j]] + s[j]);
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
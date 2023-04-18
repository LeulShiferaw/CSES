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

const int MOD = 1e9+7;

/*Iterative solution. Make sure to put in grid paths correctly because you don't start from top left.*/
void solve()
{
    int n;
    cin >> n;

    char grid[n][n];
    for(int i = n-1; i>=0; --i)
        for(int j = n-1; j>=0; --j)
            cin >> grid[i][j];
        
    int dp[n][n];
    if(grid[0][0] == '*') dp[0][0] = 0;
    else dp[0][0] = 1;
    for(int i = 0; i<n; ++i)
    {
        for(int j = 0; j<n; ++j)
        {
            if(j == 0 && i == 0) continue;
            if(grid[i][j] == '*') dp[i][j] = 0;
            else {
                int x = 0, y = 0;
                if(j != 0) x = dp[i][j-1];
                if(i != 0) y = dp[i-1][j];
                dp[i][j] = x+y;
            }
            dp[i][j] %= MOD;
        }
    }
    cout << dp[n-1][n-1] << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for(int i = a; i<b; i++)

using indexed_set =  tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

/*
    Easy formula for dp.
    Add each horizontal line and check the two recursive rectangles that follow
    Also, add each vertical line and check the two recursive rectangles that follow
*/

void solve()
{
    int a, b;
    cin >> a >> b;

    int dp[a+1][b+1];
    for(int i = 1; i<=a; ++i)
    {
        for(int j = 1; j<=b; ++j)
        {
            if(j == i) {
                dp[i][j] = 0;
                continue;
            }

            int res = INT_MAX;
            for(int k = 1; k<=i/2; ++k)
                res = min(res, dp[k][j] + dp[i-k][j] + 1);
            for(int k = 1; k<=j/2; ++k)
                res = min(res, dp[i][k] + dp[i][j-k] + 1);
            dp[i][j] = res;
        }
    }
    cout << dp[a][b] << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
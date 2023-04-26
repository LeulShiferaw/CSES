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
    Competitive programmer Handbook's formula
*/

void solve()
{
    string str1, str2;
    cin >> str1 >> str2;

    int n = str1.size(), m = str2.size();
    int dp[n+1][m+1];
    dp[0][0] = 0;
    for(int i = 0; i<=n; ++i)
    {
        for(int j = 0; j<=m; ++j)
        {
            if(i == 0 && j == 0) continue;
            int x1 = INT_MAX, x2 = INT_MAX, x3 = INT_MAX;
            if(i-1>=0) x1 = dp[i-1][j]+1;
            if(j-1>=0) x2 = dp[i][j-1]+1;
            if(i-1>=0 && j-1>=0) x3 = dp[i-1][j-1]+(str1[i-1] != str2[j-1]);
            dp[i][j] = min(x1, min(x2, x3));
        } 
    }
    cout << dp[n][m] << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
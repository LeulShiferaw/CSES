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

vector<int> getDigits(int n)
{
    vector<int> res;
    while(n != 0)
    {
        res.push_back(n%10);
        n/=10;
    }

    return res;
}

void solve()
{
    int n;
    cin >> n;

    int dp[n+1];
    dp[0] = 0;

    for(int i =1; i<=n; ++i)
    {
        int res = INT_MAX;
        auto digits = getDigits(i);
        for(const auto &dig : digits)
        {
            if(dig == 0) continue;
            res = min(res, 1+dp[i-dig]); 
        }
        dp[i] = res;
    }
    cout << dp[n] << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
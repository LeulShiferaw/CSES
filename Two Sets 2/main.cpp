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

constexpr int MOD = 1e9+7;

/*
    The trick is to find the number of subset sums of n(n+1)/4
    Use the books algorithm for find the number of sums with a bit of modification
    Instead of doing the possiblity you do the number of sums
    if n(n+1) is divisble by 4 there is a solution otherwise there is no answer.

    It counts the number of subsets twice for each subset so you have to divide the answer by 2 at the end.
    But you will be doing mod M each time. you will get (a mod m), but what you want is
    (a/2 mod m). Therefore (a/2 mod m) = (a * (1/2) mod) = (a mod m * (1/2) mod m) mod m
    (1/2) mod m is the modulo inverse of 2 for m. m is 1e9 + 7. Calculate  that using an online calculator
    and then multiply with the a mod m that I have and do mod m again to get the result.
*/

void solve()
{
    int n;
    cin >> n;

    if(n % 4 != 0 && (n+1) % 4 != 0) {
        cout << 0 << endl;
        return;
    }    

    int sum = (n*(n+1))/4;
    int dp[sum+1] = {};
    dp[0] = 1;
    for(int i=1; i<=n; ++i)
    {
        for(int j=sum-i; j>=0; --j)
        {
            dp[j+i] += dp[j];
            dp[j+i] %= MOD;
        }
    }

    ll ans = dp[sum];
    ll modInv2 = 500000004LL;
    cout << (ans * modInv2)%MOD << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
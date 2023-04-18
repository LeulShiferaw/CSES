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

bool between(const int &x, const int &m)
{
    if(x >= 1 && x <= m) return true;
    return false;
}

const int MOD = 1e9+7;

/*
    Iterative DP solution
    It basically keeps track of the count of each number ending with a number from 1 -> m in each step
    Then it adds up the values to get the total result.
*/
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> x(n);
    for(int i = 0; i<n; ++i) cin >> x[i];

    vector<ll> count(m+1, 0);
    if(x[0] == 0)
        fill(count.begin(), count.end(), 1);
    else count[x[0]] = 1;

    for(int i = 1; i<n; ++i)
    {
        vector<ll> new_count(m+1, 0);
        if(x[i] == 0)
        {
            for(int j = 1; j<=m; ++j)
            {
                if(between(j-1, m))
                {
                    new_count[j-1] += count[j];
                    new_count[j-1] %= MOD;
                }
                new_count[j] += count[j];
                new_count[j] %= MOD;
                if(between(j+1, m))
                {
                    new_count[j+1] += count[j];
                    new_count[j+1] %= MOD;
                }
            }
        }
        else {
            if(between(x[i]-1, m))
                new_count[x[i]] += count[x[i]-1];
            new_count[x[i]] += count[x[i]];
            if(between(x[i]+1, m))
                new_count[x[i]] += count[x[i]+1];
            new_count[x[i]] %= MOD;
        }
        count = new_count;
    }
    int res = 0;
    for(int c : count) {
        res += c;
        res %= MOD;
    }
    cout << res-count[0] << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
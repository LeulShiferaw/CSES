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
    Very simple dp. Just save the previous sums, update it and reset the old sums for each number iteratively.
*/

void solve()
{
    int n;
    cin >> n;

    vector<int> coins(n);
    for(int i = 0; i<n; ++i) cin >> coins[i];

    sort(coins.begin(), coins.end());

    vector<bool> sums(100000+1, false);
    sums[0] = true;
    for(int i=0; i<n; ++i)
        for(int j=100000-coins[i]; j>=0; --j)
            sums[j+coins[i]] = sums[j+coins[i]] | sums[j];

    int num_sums = 0;
    for(const auto &x : sums) {
        num_sums += x;
    }
    cout << num_sums-1 << endl;

    for(int i = 1; i<=100000; ++i)
    {
        if(sums[i]) cout << i << " ";
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
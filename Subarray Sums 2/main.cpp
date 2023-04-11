#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

/*
    I didn't solve it myself, but looked up the solution
*/
void solve()
{
    int n, x;
    cin >> n >> x;

    vll a(n);
    for(int i = 0; i<n; ++i) cin >> a[i];

    map<long long, int> sums;
    sums[0] = 1;

    long long curr_sum = 0;
    long long res = 0;
    for(int i = 0; i<n; ++i)
    {
        curr_sum += a[i];

        if(sums.find(curr_sum - x) != sums.end())//curr_sum = a1+a2+a3...ai, if we want the last few ak+...+ai to be sum. Just find how many curr_sum - x are prefix sums
            res += sums[curr_sum-x];
        sums[curr_sum]++;
    }
    cout << res << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
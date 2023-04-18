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

ll lim = 1000'000'000 + 7;

/*Straight forward book solution*/
void solve()
{
    int n;
    cin >> n;

    long long count[n+1];
    for(int i = 0; i<=n; ++i) count[i] = -1;

    count[0] = 0;
    for(int i = 1; i<=n; ++i)
    {
        long long ans = 0;
        for(int j = 1; j<=6; ++j)
        {
            if(i-j < 0) break;
            if(j==i) ++ans;
            else ans += count[i-j];
            ans %= lim;
        }
        count[i] = ans;
    }    
    cout << count[n] << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
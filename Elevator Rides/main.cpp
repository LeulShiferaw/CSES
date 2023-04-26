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

template <typename T>
void display(const vector<T> &v)
{
    for(const auto &x : v) cout << x << " ";
    cout << endl;
}

/*
    Book's algorithm with slight modification. There has to be a {1, 0} on the 0th best.
*/

void solve()
{
    int n, x;
    cin >> n >> x;

    vi w(n);
    for(int i = 0; i<n; ++i) cin >> w[i];    

    auto lim = 1<<n;
    pi best[lim];
    best[0] = {1, 0};
    for(int s = 1; s<lim; ++s)
    {
        best[s] = {n+1, 0};
        for(int p = 0; p<n; ++p)
        {
            if(((1<<p) & s) == 0) continue;
            auto opt = best[s ^ (1<<p)];
            if(opt.second + w[p] <= x)
            {
                opt.second += w[p];
            }
            else {
                ++opt.first;
                opt.second = min(opt.second, w[p]);
            }
            best[s] = min(best[s], opt);
        }
    }
    cout << best[(1<<n)-1].first << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
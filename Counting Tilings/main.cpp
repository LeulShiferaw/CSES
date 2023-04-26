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

int number_bits(int n)
{
    return floor(log2(n)) + 1;
}

int flipBits(int n)
{
    return ~n & ((1 << number_bits(n))-1);
}

void solve()
{
    int n, m;
    cin >> n >> m;    

    int dp[m+1][(1<<n)];
    for(int i = 0; i<(1<<n); ++i)
        dp[1][i] = 1;
    
    for(int i= 2; i<=m; ++i)
    {
        for(int si = 0; si<(1<<n); ++si)
        {
            dp[i][si] = 0;
            for(int sj = 0; sj<(1<<n); ++sj) {
                int flip_si = flipBits(si);
                if((flip_si & sj) == flip_si) dp[i][si] += dp[i-1][sj];
            }
        }
    }
    cout << dp[m][(1<<n)-1] << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
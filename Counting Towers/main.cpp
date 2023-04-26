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

constexpr int num_sets = 1<<3;
constexpr int MOD = (int)1e9 + 7;


void solve()
{
    int t;
    cin >> t;

    while(t--)
    {
        int n;
        cin >> n;

        int dp[1'000'000+1][2]{0};
        REP(i, 0, num_sets) dp[0][i] = 1;
        REP(i, 1, n+1) {
            REP(j, 0, num_sets) {
                if(j == 0b001 || j == 0b010) {
                    dp[i][j] = 0;
                    continue;
                }

                if(i == 1) {
                    dp[i][j] = 1;
                    continue;
                }

                if((j & (1<<2)) == 0) {
                    dp[i][j] += dp[i-1][0b000];
                    dp[i][j] %= MOD;
                    dp[i][j] += dp[i-1][0b111];
                    dp[i][j] %= MOD;
                    dp[i][j] += dp[i-1][0b011];
                    dp[i][j] %= MOD;
                    continue;
                }

                int sum = 0;
                REP(k, 0, num_sets) {
                    if(k == 0) continue;
                    sum += dp[i-1][k];
                    sum %= MOD;
                }
                dp[i][j] = sum;
            }
        }

        int res = 0;
        REP(i, 0, num_sets) {
            if((i & (1<<0)) == 0 || (i & (1<<1)) == 0) continue;
            res += dp[n][i];
            res %= MOD;
        }
        cout << res << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
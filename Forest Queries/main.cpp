#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define endl "\n"
#define REP(i, a, b) for(int i = a; i<b; i++)
#define rREP(i, b, a) for(int i = b; i>=a; i--)

using indexed_set =  tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;

template <typename T>
using pr = pair<T, T>;

template <typename T>
using vc = vector<T>;

template <typename T>
using vv = vector<vector<T>>;

constexpr int MOD = 1e9+7;

template <typename T>
void display(const vector<T> &v)
{
    for(const auto &x : v) cout << x << " ";
    cout << endl;
}

void solve()
{
    int n, q;
    cin >> n >> q;

    char grid[n][n];
    REP(i, 0, n) {
        REP(j, 0, n) {
            cin >> grid[i][j];
        }
    }

    int dp[n][n];
    REP(i, 0, n) {
        int curr = 0;
        REP(j, 0, n) {
            if(grid[i][j] == '*') ++curr;
            dp[i][j] = 0;
            if((i-1) >= 0) dp[i][j] += dp[i-1][j];
            dp[i][j] += curr;
        }
    }

    REP(i, 0, q) {
        int x1, y1, x2, y2;
        cin >> y1 >> x1 >> y2 >> x2;

        --x1; --x2; --y1; --y2;
        int res = dp[y2][x2];
        if(y1-1 >= 0) {
            if((x1-1) >= 0) {
                res += dp[y1-1][x1-1];
            }
            res -= dp[y1-1][x2];
        }
        if((x1-1) >= 0) {
            res -= dp[y2][x1-1];
        }
        std::cout << res << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
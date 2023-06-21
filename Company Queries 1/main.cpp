#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define all(x) (x).begin(), (x).end()
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define endl "\n"
#define REP(i, a, b) for(int i = a; i<b; i++)
#define rREP(i, b, a) for(int i = b; i>=a; i--)

template <typename T>
using indexed_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

/*Same concept as successor graphs*/

void solve()
{
    int n, q;
    cin >> n >> q;

    int boss[n+1];
    boss[0] = 0;
    boss[1] = 0;
    REP(i, 2, n+1) {
        int e;
        cin >> e;

        boss[i] = e;
    }

    int lim = (int)floor(log2(2e5)) + 1;
    int ancestor[n+1][lim];
    for(int i = 0; i<=n; ++i) {
        ancestor[i][0] = boss[i];
    }

    for(int i = 1; i<lim; ++i) {
        for(int j = 0; j<=n; ++j) {
            ancestor[j][i] = ancestor[ancestor[j][i-1]][i-1];
        }
    }

    REP(i, 0, q) {
        int x, k;
        cin >> x >> k;

        int curr = x;
        for(int currLog = 0; k>0; k/=2, ++currLog) {
            if(k % 2 == 1) {
                curr = ancestor[curr][currLog];
            }
        }
        if(curr == 0) cout << -1 << "\n";
        else cout << curr << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
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

    vc<int> x(n+1);
    REP(i, 1, n+1) {
        cin >> x[i];
    }

    vc<ll> sums(n+1);
    sums[0] = 0ll;
    for(int i = 1; i<=n; ++i) {
        sums[i] = sums[i-1] + x[i];
    }

    REP(i, 0, q) {
        int a, b;
        cin >> a >> b;

        cout << sums[b] - sums[a-1] << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
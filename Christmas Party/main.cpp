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

void solve()
{
    int n;
    cin >> n;

    long long fac[n+1];
    fac[0] = 1;
    for(int i = 1; i<=n; ++i) {
        fac[i] = fac[i-1] * i;
        fac[i] %= MOD;
    }

    long long f[n+1];
    f[1] = 0;
    f[2] = 1;
    long long fk = n*(n-1)
    for(int i = 3; i<=n; ++i) {
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
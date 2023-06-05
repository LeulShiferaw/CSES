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

using indexed_set =  tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>;

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

vc<ll> diffArray(const vc<ll> &vec) {
    vc<ll> res;
    res.PB(vec[0]);
    for(int i = 1; i<(int)vec.size(); ++i) {
        res.PB(vec[i]-vec[i-1]);
    }
    return res;
}

void solve()
{
    //Technique one use pair of index and value with indexed set policy data structure
    int n;
    cin >> n;

    indexed_set st;
    vc<int> x(n);
    REP(i, 0, n) {
        cin >> x[i];
        st.insert(make_pair(i, x[i]));
    }

    vc<int> p(n);
    REP(i, 0, n) cin >> p[i];

    for(int i = 0; i<n; ++i) {
        auto res = st.find_by_order(p[i]-1);
        cout << res->second << " ";
        st.erase(res);
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
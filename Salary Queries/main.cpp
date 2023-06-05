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

//Use technique: index compression
//in this case the index compression is just using the p vector
void solve()
{
    int n, q;
    cin >> n >> q;

    indexed_set<pair<int, int>> valInd;

    vector<int> p(n);
    REP(i, 0, n) {
        cin >> p[i];
        valInd.insert(make_pair(p[i], i));
    }
    

    REP(i, 0, q) {
        char c;
        cin >> c;

        if(c == '!') {
            int k, x;
            cin >> k >> x;

            auto itr = valInd.find(make_pair(p[k-1], k-1));
            valInd.erase(itr);
            valInd.insert(make_pair(x, k-1));
            p[k-1] = x;
        } else {
            int a, b;
            cin >> a >> b;

            int res = valInd.order_of_key(make_pair(b, (int)2e9)) - valInd.order_of_key(make_pair(a, -1));
            cout << res << endl;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
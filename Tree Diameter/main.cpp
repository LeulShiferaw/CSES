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

pair<int, int> longestPathNode(vc<int> tree[], int curr, int prev) {
    if (prev == 0) {
        if (tree[curr].size() == 0) {
            return make_pair(0, curr);
        }
    }
    else if (tree[curr].size() - 1 == 0) {
        return make_pair(0, curr);
    }

    pair<int, int> res = make_pair(0, 0);
    for (auto& x : tree[curr]) {
        if (x == prev) continue;
        auto temp = longestPathNode(tree, x, curr);
        res = max(res, temp);
    }
    res.first++;
    return res;
}

void solve()
{
    int n;
    cin >> n;

    vc<int> tree[n+1];
    for(int i =0; i<n-1; ++i) {
        int a, b;
        cin >> a >> b;

        tree[a].push_back(b);
        tree[b].push_back(a);  
    }

    auto res1 = longestPathNode(tree, 1, 0);
    auto res2 = longestPathNode(tree, res1.second, 0);
    cout << res2.first << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
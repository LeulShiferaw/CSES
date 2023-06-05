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

//Solved using indexed set
//Just keep getting the 1k, 2k, 3k th digits

void solve()
{
    int n, k;
    cin >> n >> k;

    indexed_set<int> children;
    for(int i = 1; i<=n; ++i) children.insert(i);

    int curr = k;
    while(children.size() > 0) {
        curr %= children.size();
        auto toBeRemoved = children.find_by_order(curr);
        cout << *toBeRemoved << " ";
        children.erase(toBeRemoved);
        curr += k;
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
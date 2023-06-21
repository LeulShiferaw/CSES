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

constexpr int MAXN = 2e5+1;

vc<int> c;
vc<int> Tree[MAXN+1];
int numDistinct[MAXN+1];

unordered_set<int> dfs(int curr, int prev) {
    unordered_set<int> newSet;
    newSet.insert(c[curr]);
    for(auto &x : Tree[curr]) {
        if(x == prev) continue;
        auto temp = dfs(x, curr);
        if(temp.size() > newSet.size()) swap(newSet, temp); //This is the key otherwise it is time limit exceeded
        for(auto &u : temp) newSet.insert(u);
    }
    numDistinct[curr] = newSet.size();
    return newSet;
}

void solve()
{
    int n;
    cin >> n;

    c.resize(n+1);
    REP(i, 1, n+1) {
        cin >> c[i];
    }

    REP(i, 0, n-1) {
        int a, b;
        cin >> a >> b;

        Tree[a].pb(b);
        Tree[b].pb(a);
    }

    dfs(1, 0);
    for(int i = 1; i<=n; ++i) {
        cout << numDistinct[i] << " ";
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
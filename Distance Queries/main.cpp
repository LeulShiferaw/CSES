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

void dfs(vc<int> tree[], int curr, int prev, vv<int> &ancestor, vc<int> &depth) {
    ancestor[curr][0] = prev;
    if(prev == 0) depth[curr] = 0;
    else depth[curr] = depth[prev] + 1;
    for(auto &x : tree[curr]) {
        if(x == prev) continue;
        dfs(tree, x, curr, ancestor, depth);
    }
}

int kthAncestor(int x, int k, vv<int> &ancestor) {
    int curr = x;
    for(int currLog = 0; k>0; k/=2, ++currLog) {
        if(k % 2 == 1) {
            curr = ancestor[curr][currLog];
        }
    }
    return curr;
}

int lca(int a, int b, vv<int> &ancestor, vc<int> &depth) {
    if(depth[a] < depth[b]) swap(a, b);
    a = kthAncestor(a, depth[a]-depth[b], ancestor);
    if(a == b) return a;

    int LOG = (int)floor(log2(2e5)) + 1;
    for(int i = LOG-1; i>=0; --i) {
        if(ancestor[a][i] != ancestor[b][i]) {
            a = ancestor[a][i];
            b = ancestor[b][i];
        }
    }
    return ancestor[a][0];
}

void solve()
{
    int n, q;
    cin >> n >> q;

    vc<int> tree[n+1];
    REP(i, 0, n-1) {
        int a, b;
        cin >> a >> b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    int lim = (int)floor(log2(2e5)) + 1;
    vc<int> depth(n+1, -1);
    vv<int> ancestor(n+1, vc<int>(lim));
    dfs(tree, 1, 0, ancestor, depth);
    for(int i=1; i<lim; ++i) {
        for(int j=1; j<=n; ++j) {
            ancestor[j][i] = ancestor[ancestor[j][i-1]][i-1];
        }
    }

    REP(i, 0, q) {
        int a, b;
        cin >> a >> b;

        cout << depth[a] + depth[b] - 2*depth[lca(a, b, ancestor, depth)] << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
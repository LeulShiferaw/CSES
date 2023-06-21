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

int kthAncestor(vv<int> &ancestor, int x, int k) {
    int curr = x;
    for(int currLog = 0; k>0; k/=2, ++currLog) {
        if(k % 2 == 1) {
            curr = ancestor[curr][currLog];
        }
    }
    return curr;
}

void getDepth(vc<int> tree[], int curr, int prev, vc<int> &depth) {
    if(prev == 0) {
        depth[curr] = 0;
    }
    else {
        depth[curr] = depth[prev]+1;
    }

    for(auto &x : tree[curr]) {
        if(x == prev) continue;
        getDepth(tree, x, curr, depth);
    }
}

int lca(int a, int b, vc<int> &depth, vv<int> &ancestor) {
    if(depth[a] < depth[b]) swap(a,b);
    a = kthAncestor(ancestor, a, depth[a]-depth[b]);
    if(a == b) return a;
    int LOGN = (int)floor(log2(2e5));
    for(int i=LOGN; i>=0; --i) {
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

    int boss[n+1];
    boss[0] = 0;
    boss[1] = 0;
    vc<int> tree[n+1];
    REP(i, 2, n+1) {
        int e;
        cin >> e;

        boss[i] = e;
        tree[e].push_back(i);
    }

    int lim = (int)floor(log2(2e5)) + 1;
    vv<int> ancestor(n+1, vc<int>((int)floor(log2(2e5)) + 1));
    for(int i = 0; i<=n; ++i) {
        ancestor[i][0] = boss[i];
    }

    for(int i = 1; i<lim; ++i) {
        for(int j = 0; j<=n; ++j) {
            ancestor[j][i] = ancestor[ancestor[j][i-1]][i-1];
        }
    }

    vc<int> depth(n+1, -1);
    getDepth(tree, 1, 0, depth);

    REP(i, 0, q) {
        int a, b;
        cin >> a >> b;

        cout << lca(a, b, depth, ancestor) << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
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
/*
    Uses Heavy light decomposition
    Watch Pavel Mavrin's youtube tutorial on it
    There is any easier way of doing this and that is 
    by just adding one to value at a and b and subtracting one at lca and the node before that.
*/

//Uses 0 indexing
class SegTree {
public:
    int n;
    bool init = false;
    vc<ll> tree;
    SegTree() {};
    SegTree(int siz) {
        int nearPow2 = (1 << (int)ceil(log2(siz)));
        n = nearPow2;
        tree.resize(2 * nearPow2, 0);
        init = true;
    }
    void initialize(int siz) {
        int nearPow2 = (1 << (int)ceil(log2(siz)));
        n = nearPow2;
        tree.resize(2 * nearPow2, 0);
        init = true;
    }
    ll get(int k) {
        --k;
        return tree[n + k];
    }
    //n is the size of input
    //incase input is like size n+1
    void build(const vc<ll>& input) {
        if (!init) initialize(input.size());
        for (int i = 0; i < (int)input.size(); ++i) {
            tree[n + i] = input[i];
        }
        for (int i = n - 1; i >= 1; --i) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }
    ll sum(int a, int b) {
        --a; --b;
        a += n; b += n;
        ll res = 0;
        while (a <= b) {
            if (a % 2 == 1) res = res + tree[a++];
            if (b % 2 == 0) res = res + tree[b--];
            a /= 2; b /= 2;
        }
        return res;
    }
    void set(int k, int u) {
        update(k, u - tree[k - 1 + n]);
    }
    void update(int k, int x) {
        --k;
        k += n;
        tree[k] += x;
        for (k /= 2; k >= 1; k /= 2) {
            tree[k] = tree[2 * k] + tree[2 * k + 1];
        }
    }
};

constexpr int MAXN = 2e5 + 1;
int values[MAXN + 1];
int depth[MAXN + 1];
int heavy[MAXN + 1];
int parent[MAXN + 1];
int original[MAXN + 1];
vc<int> Tree[MAXN + 1];
int top[MAXN + 1];
vc<int> heavyTraverse;
int heavy_index[MAXN + 1];
int num_nodes[MAXN + 1];

int dfs(int curr, int prev) {
    if (prev == 0) depth[curr] = 0;
    else depth[curr] = depth[prev] + 1;
    parent[curr] = prev;
    int res = 0;
    for (auto& x : Tree[curr]) {
        if (x == prev) continue;
        res += dfs(x, curr);
    }
    num_nodes[curr] = res + 1;
    return res + 1;
}

int calcHeavy(int curr, int prev) {
    int ind = -1;
    int mx = -1;
    for (auto& x : Tree[curr]) {
        if (x == prev) continue;
        if (num_nodes[x] > mx) {
            mx = num_nodes[x];
            ind = x;
        }
        calcHeavy(x, curr);
    }
    heavy[curr] = ind;
    return mx;
}

void calcTop(int curr, int prev, int tp) {
    top[curr] = tp;
    for (auto& x : Tree[curr]) {
        if (x == prev) continue;
        if (x == heavy[curr]) {
            calcTop(x, curr, tp);
        }
        else {
            calcTop(x, curr, x);
        }
    }
}

void heavyTraversal(int curr, int prev) {
    heavy_index[curr] = heavyTraverse.size();
    heavyTraverse.push_back(curr);
    if (heavy[curr] != -1)
        heavyTraversal(heavy[curr], curr);
    for (auto& x : Tree[curr]) {
        if (x == prev || x == heavy[curr]) continue;
        heavyTraversal(x, curr);
    }
}

void rangeUpdate(int a, int b, int x) {
    if (a > b) swap(a, b);
    values[a] += x;
    if(b+1 <= MAXN) {
        values[b+1] -= x;
    }
}

void heavyLight(int a, int b) {
    int x, y;
    while (true) {
        x = top[a], y = top[b];
        if (x == y) {
            rangeUpdate(heavy_index[a] + 1, heavy_index[b] + 1, 1);
            return;
        }

        if (depth[x] > depth[y]) {
            rangeUpdate(heavy_index[x] + 1, heavy_index[a] + 1, 1);
            a = parent[x];
        }
        else {
            rangeUpdate(heavy_index[y] + 1, heavy_index[b] + 1, 1);
            b = parent[y];
        }
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;

    REP(i, 0, n - 1) {
        int a, b;
        cin >> a >> b;

        Tree[a].push_back(b);
        Tree[b].push_back(a);
    }

    dfs(1, 0);
    calcHeavy(1, 0);
    calcTop(1, 0, 1);
    heavyTraversal(1, 0);

    REP(i, 0, m) {
        int a, b;
        cin >> a >> b;
        heavyLight(a, b);
    }

    int curr_sum = 0;
    for (int i = 1; i <= n; ++i) {
        curr_sum += values[i];
        original[heavyTraverse[i-1]] = curr_sum;
    }
    for (int i = 1; i <= n; ++i) {
        cout << original[i] << " ";
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
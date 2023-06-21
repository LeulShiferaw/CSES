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

//Solution done using heavy light decomposition

//Uses 0 indexing
class SegMaxTree {
public:
    int n;
    vc<ll> tree;
    SegMaxTree() {};
    ll get(int k) {
        --k;
        return tree[n + k];
    }
    //n is the size of input
    //incase input is like size n+1
    void build(const vc<ll>& input) {
        int nearPow2 = (1 << (int)ceil(log2(input.size())));
        n = nearPow2;
        tree.resize(2 * nearPow2, 0);

        for (int i = 0; i < (int)input.size(); ++i) {
            tree[n + i] = input[i];
        }
        for (int i = n - 1; i >= 1; --i) {
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }
    ll maximum(int a, int b) {
        --a; --b;
        a += n; b += n;
        ll res = -1;
        while (a <= b) {
            if (a % 2 == 1) res = max(res, tree[a++]);
            if (b % 2 == 0) res = max(res, tree[b--]);
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
            tree[k] = max(tree[2 * k], tree[2 * k + 1]);
        }
    }
};

constexpr int MAXN = 2e5 + 1;

vc<int> v;
vc<int> Tree[MAXN + 1];
int numNodes[MAXN + 1];
int heavy[MAXN + 1];
int heavyIndex[MAXN + 1];
int top[MAXN + 1];
int depth[MAXN + 1];
vc<ll> heavyTrav;
int parent[MAXN + 1];
SegMaxTree segT;

int dfs(int curr, int prev) {
    parent[curr] = prev;
    depth[curr] = 1;
    if (prev != 0)
        depth[curr] = depth[prev] + 1;
    int res = 1;
    for (auto& x : Tree[curr]) {
        if (x == prev) continue;
        res += dfs(x, curr);
    }
    numNodes[curr] = res;
    return res;
}

void calcHeavy(int curr, int prev) {
    int res = 0;
    int ind = 0;
    for (auto& x : Tree[curr]) {
        if (x == prev) continue;
        if (numNodes[x] > res) {
            res = numNodes[x];
            ind = x;
        }
        calcHeavy(x, curr);
    }
    heavy[curr] = ind;
}

void heavyTraverse(int curr, int prev) {
    heavyTrav.push_back(v[curr - 1]);
    heavyIndex[curr] = heavyTrav.size();
    if (heavy[curr] != 0)
        heavyTraverse(heavy[curr], curr);
    for (auto& x : Tree[curr]) {
        if (x == prev || x == heavy[curr]) continue;
        heavyTraverse(x, curr);
    }
}

void calcTop(int curr, int prev, int tp) {
    top[curr] = tp;
    if (heavy[curr] != 0) {
        calcTop(heavy[curr], curr, tp);
    }
    for (auto& x : Tree[curr]) {
        if (x == prev || x == heavy[curr]) continue;
        calcTop(x, curr, x);
    }
}

ll heavyLight(int a, int b) {
    int x, y;
    ll res = -1;
    while (true) {
        x = top[a]; y = top[b];
        if (x == y) {
            if (heavyIndex[a] < heavyIndex[b]) {
                res = max(res, segT.maximum(heavyIndex[a], heavyIndex[b]));
            }
            else {
                res = max(res, segT.maximum(heavyIndex[b], heavyIndex[a]));
            }
            return res;
        }

        if (depth[x] > depth[y]) {
            if (heavyIndex[x] < heavyIndex[a]) {
                res = max(res, segT.maximum(heavyIndex[x], heavyIndex[a]));
            }
            else res = max(res, segT.maximum(heavyIndex[a], heavyIndex[x]));
            a = parent[x];
        }
        else {
            if (heavyIndex[y] < heavyIndex[b]) {
                res = max(res, segT.maximum(heavyIndex[y], heavyIndex[b]));
            }
            else res = max(res, segT.maximum(heavyIndex[b], heavyIndex[y]));
            b = parent[y];
        }
    }
    return res;
}

void solve()
{
    int n, q;
    cin >> n >> q;

    v.resize(n);
    REP(i, 0, n) {
        cin >> v[i];
    }

    REP(i, 0, n - 1) {
        int a, b;
        cin >> a >> b;

        Tree[a].pb(b);
        Tree[b].pb(a);
    }

    dfs(1, 0);
    calcHeavy(1, 0);
    heavyTraverse(1, 0);
    calcTop(1, 0, 1);
    segT.build(heavyTrav);

    REP(i, 0, q) {
        int choice;
        cin >> choice;

        if (choice == 1) {
            int s, x;
            cin >> s >> x;
            segT.set(heavyIndex[s], x);
        }
        else {
            int a, b;
            cin >> a >> b;
            cout << heavyLight(a, b) << endl;
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
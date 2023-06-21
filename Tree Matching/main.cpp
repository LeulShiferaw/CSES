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

pair<int, int> longestPathNode(vc<int> tree[], int curr, int prev, vector<int>& before) {
    stack<pair<int, int>> st;
    if (prev == 0) {
        if (tree[curr].size() == 0) {
            before[curr] = 0;
            return make_pair(0, curr);
        }
    }
    else if (tree[curr].size() - 1 == 0) {
        before[curr] = 0;
        return make_pair(0, curr);
    }
    int addToPath = 0;
    pair<int, int> res = make_pair(0, 0);
    for (auto& x : tree[curr]) {
        if (x == prev) continue;
        auto temp = longestPathNode(tree, x, curr, before);
        if (temp.first > res.first || addToPath == 0) {
            addToPath = x;
        }
        res = max(res, temp);
    }
    before[curr] = addToPath;
    res.first++;
    return res;
}

int getDepth(vc<int> tree[], int curr, int prev, vc<int> &depth) {
    if(depth[curr] != -1) return depth[curr];
    if(prev == 0) {
        if(tree[curr].size() == 0) {
            depth[curr] = 0;
            return 0;
        }
    } else if(tree[curr].size()-1 == 0) {
        depth[curr] = 0;
        return 0;
    }
 
    int res = 0;
    for(auto &x : tree[curr]) {
        if(x == prev) continue;
        res = max(getDepth(tree, x, curr, depth), res);
    }
    ++res;
    depth[curr] = res;
    return res;
}

int getMaxMatch(vc<int> tree[], int curr, int prev, int dp[][2], vc<bool> &used) {
}

void solve()
{
    int n;
    cin >> n;

    vc<int> tree[n+1];
    REP(i, 0, n - 1) {
        int a, b;
        cin >> a >> b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    int dp[n+1][2];
    for(int i = 0; i<2; ++i) {
        REP(j, 0, n+1) {
            dp[j][i] = -1;
        }
    }
    vc<bool> used(n+1, false);
    cout << getMaxMatch(tree, 1, 0, dp, used) << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
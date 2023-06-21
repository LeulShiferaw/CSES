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
    uses centroid decomposition, the first method used an unordered_map
    but the only one that works is using an array instead
*/

constexpr int MAXN = 2e5+1;

int k;
vc<int> Tree[MAXN+1];
bool centroid[MAXN+1];
ll numPaths = 0;
int numNodes[MAXN+1];
int cnt[MAXN+1];
int max_depth = 0;

int dfs(int curr, int prev) {
    int res = 1;
    for(auto &x : Tree[curr]) {
        if(x == prev || centroid[x]) continue;
        res += dfs(x, curr);
    }
    numNodes[curr] = res;
    return res;
}

int findCentroid(int curr, int prev, int head) {
    int mx = -1, ind = 0;
    
    for(auto &x : Tree[curr]) {
        if(x == prev || centroid[x]) continue;
        if(numNodes[x] > mx) {
            mx = numNodes[x];
            ind = x;
        }
    }

    if(mx <= floor(numNodes[head]/2)) {
        return curr;
    }
    else {
        if(ind == 0) return -1;
        else return findCentroid(ind, curr, head);
    }
}

void calc_depths(int curr, int prev, int depth) {
    cnt[depth]++;
    for(auto &x : Tree[curr]) {
        if(x == prev || centroid[x]) continue;
        calc_depths(x, curr, depth+1);
    }
}

void calc_paths(int curr, int prev, int depth) {
    max_depth = max(max_depth, depth);
    if(k-depth >= 0)
        numPaths += cnt[k-depth];
    for(auto &x : Tree[curr]) {
        if(x == prev || centroid[x]) continue;
        calc_paths(x, curr, depth+1);
    }
}

void centroid_decomp(int curr) {
    dfs(curr, 0);
    int cent = findCentroid(curr, 0, curr);
    centroid[cent] = true;

    max_depth = 0;
    cnt[0] = 1;
    for(auto &x : Tree[cent]) {
        if(centroid[x]) continue;
        calc_paths(x, cent, 1);
        calc_depths(x, cent, 1);
    }

    for(int i = 0; i<=max_depth; ++i) cnt[i] = 0;

    for(auto &x : Tree[cent]) {
        if(centroid[x]) continue;
        centroid_decomp(x);
    }
}

void solve()
{
    int n;
    cin >> n >> k;

    REP(i, 0, n-1) {
        int a, b;
        cin >> a >> b;

        Tree[a].pb(b);
        Tree[b].pb(a);
    }

    centroid_decomp(1);
    cout << numPaths << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
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

int getNumNodes(vc<int> tree[], int curr, int prev, vc<int> &numNodes) {
    if(numNodes[curr] != -1) return numNodes[curr];

    int res = 0;
    for(auto &x : tree[curr]) {
        if(x == prev) continue;
        res += getNumNodes(tree, x, curr, numNodes);
    }
    ++res;
    numNodes[curr] = res;
    return res;
}

ll getDistance(vc<int> tree[], int curr, int prev, vc<int> &numNodes, vc<ll> &distance)
{
    if(distance[curr] != -1) return distance[curr];

    ll res = 0;
    for(auto &x : tree[curr]) {
        if(x == prev) continue;
        res += getDistance(tree, x, curr, numNodes, distance) + numNodes[x];
    }
    distance[curr] = res;
    return res;
}

void getParents(vc<int> tree[], int curr, int prev, vc<int> &parent) {
    parent[curr] = prev;
    for(auto &x : tree[curr]) {
        if(x == prev) continue;
        getParents(tree, x, curr, parent);
    }
}

//Distance2 is complete distance from both upwards and downwards
void getDistance2(vc<int> tree[], int curr, vc<int>& parent, vc<int>& numNodes, vc<ll>& distance, vc<ll>& distance2) {
    if (distance2[curr] != -1) return;
    ll val1 = 0;
    for (auto& x : tree[curr]) {
        if (x == parent[curr]) continue;
        val1 += distance[x] + numNodes[x];
    }

    ll val2 = 0;
    if (parent[curr] == 0) {
        val2 = 0;
    }
    else {
        val2 += distance2[parent[curr]] + numNodes[1] - numNodes[curr];
        val2 -= distance[curr] + numNodes[curr];
    }
    distance2[curr] = val1 + val2;

    for (auto& x : tree[curr]) {
        if (x == parent[curr]) continue;
        getDistance2(tree, x, parent, numNodes, distance, distance2);
    }
}

void solve()
{
    int n;
    cin >> n;

    vc<int> tree[n+1];
    REP(i, 0, n-1) {
        int a, b;
        cin >> a >> b;

        tree[a].pb(b);
        tree[b].pb(a);
    }
    
    vc<int> numNodes(n+1, -1);
    vc<ll> distance(n+1, -1); 
    vc<ll> distance2(n+1, -1);
    vc<int> parent(n+1, 0);
    getParents(tree, 1, 0, parent);
    getNumNodes(tree, 1, 0, numNodes);
    getDistance(tree, 1, 0, numNodes, distance);
    getDistance2(tree, 1, parent, numNodes, distance, distance2);
    for(int i = 1; i<(int)distance2.size(); ++i) {
        cout << distance2[i] << " ";
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
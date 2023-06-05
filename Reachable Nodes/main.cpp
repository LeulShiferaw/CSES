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

using indexed_set =  tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

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

void topo_sort(vc<int> graph[], vc<int> &state, int curr, vc<int> &topology) {
    if(state[curr] == 2) return;
    state[curr] = 1;
    for(auto &node : graph[curr]) {
        topo_sort(graph, state, node, topology);
    }
    state[curr] = 2;
    topology.PB(curr);
}

vc<int> topo_sort(vc<int> graph[], int n) {
    vc<int> state(n+1, 0);
    vc<int> topology;
    for(int i = 1; i<=n; ++i) {
        if(state[i] == 0) {
            topo_sort(graph, state, i, topology);
        }
    }
    reverse(topology.begin(), topology.end());
    return topology;
}

//Use the book's algorithm using bit-parallel algorithm
//Make sure to do it on the reverse of the topology

void solve()
{
    int n, m;
    cin >> n >> m;

    vc<int> graph[n+1];
    REP(i, 0, m) {
        int a, b;
        cin >> a >> b;

        graph[a].push_back(b);
    }

    auto topology = topo_sort(graph, n);

    bitset<(int)5e4+1> reach[n+1];
    for(int i = topology.size()-1; i>=0; --i) {
        reach[topology[i]][topology[i]] = 1;
        for(auto &edge : graph[topology[i]]) {
            reach[topology[i]] |= reach[edge];
        }
    }

    for(int i = 1;i<=n; ++i) {
        cout << reach[i].count() << " ";
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
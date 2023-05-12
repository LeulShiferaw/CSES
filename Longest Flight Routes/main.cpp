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

class DSU {
    public:
        vector<int> parent;
        vector<int> size;
    public:
        DSU(int n) :parent(n+1, -1), size(n+1, 1) {}
        int find(int n) {
            if(parent[n] == -1) return n;
            while(true)
            {
                if(parent[n] == -1) return n;
                n = parent[n];
            }
        }

        void unite(int a, int b) {
            int pa = find(a);
            int pb = find(b);
            if(pa == pb) return;
            if(size[pa] < size[pb]) swap(pa, pb);
            size[pa] += size[pb];
            parent[pb] = pa;
        }

        bool same(int a, int b) {
            return find(a) == find(b);
        }
};

//Get the topological sort and apply DP on it
//To find the longest path for each i
//Get its neighbors in the reverse graph and 
//get the one with the maximum distance from i
//and just add one to it

void dfs(vc<int> graph[], vc<int> &state, int curr, vc<int> &topology) {
    if(state[curr] == 2) return;

    state[curr] = 1;
    for(auto &node : graph[curr]) {
        dfs(graph, state, node, topology);
    }
    state[curr] = 2;
    topology.PB(curr);
}

constexpr int INF = 1e6+1;
void solve()
{
    int n, m;
    cin >> n >> m;

    vc<int> graph[n+1];
    vc<int> rgraph[n+1];
    REP(i, 0, m) {
        int a, b;
        cin >> a >> b;

        graph[a].PB(b);
        rgraph[b].PB(a);
    }

    //Get the topological sort from 1
    vc<int> topology;
    vc<int> state(n+1, 0);
    dfs(graph, state, 1, topology);
    reverse(topology.begin(), topology.end());
    bool ok = false;

    //If the topology doesn't have n in it, it is impossible
    for(auto &node : topology) {
        if(node == n) {
            ok = true;
            break;
        }
    }
    if(ok)
    {
        vc<int> dp(n+1, -1);
        for(int i= 0; i<(int)topology.size(); ++i) {
            if(topology[i] == 1) {
                dp[1] = 1;
                continue;
            }
            int max_node = -INT_MAX;
            for(auto &node : rgraph[topology[i]]) {
                max_node = max(max_node, dp[node]);
            }
            dp[topology[i]] = max_node+1;
        }
        cout << dp[n] << endl;

        //Backtracking the path
        vc<int> path;
        int curr = n;
        while(true) {
            path.push_back(curr);
            if(curr == 1) {
                break;
            }
            for(auto &node : rgraph[curr]) {
                if(dp[node] == dp[curr]-1) {
                    curr = node;
                    break;
                }
            }
        }
        reverse(path.begin(), path.end());
        display(path);
    }
    else {
        cout << "IMPOSSIBLE" << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
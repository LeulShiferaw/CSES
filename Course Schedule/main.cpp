#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define endl "\n"
#define REP(i, a, b) for(int i = a; i<b; i++)
#define rREP(i, b, a) for(int i = b; i>=a; i--)

using ll = long long;

template <typename T>
using pr = pair<T, T>;

template <typename T>
using vc = vector<T>;

template <typename T>
using vv = vector<vector<T>>;

constexpr int MOD = 1e9 + 7;

template <typename T>
void display(const vector<T>& v)
{
    for (const auto& x : v) cout << x << " ";
    cout << endl;
}

class DSU {
public:
    vector<int> parent;
    vector<int> size;
public:
    DSU(int n) :parent(n + 1, -1), size(n + 1, 1) {}
    int find(int n) {
        if (parent[n] == -1) return n;
        while (true)
        {
            if (parent[n] == -1) return n;
            n = parent[n];
        }
    }

    void unite(int a, int b) {
        int pa = find(a);
        int pb = find(b);
        if (pa == pb) return;
        if (size[pa] < size[pb]) swap(pa, pb);
        size[pa] += size[pb];
        parent[pb] = pa;
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }
};

bool dfs(vc<int> graph[], vc<int>& state, int curr, vc<int>& topology)
{
    if (state[curr] == 2) {
        return false;
    }
    else if (state[curr] == 1) {
        return true;
    }

    state[curr] = 1;
    for (auto& node : graph[curr]) {
        if (dfs(graph, state, node, topology)) {
            return true;
        }
    }
    state[curr] = 2;
    topology.push_back(curr);
    return false;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    vc<int> graph[n + 1];
    REP(i, 0, m) {
        int a, b;
        cin >> a >> b;

        graph[a].PB(b);
    }

    vc<int> topology;
    vc<int> state(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (state[i] == 0) {
            if (dfs(graph, state, i, topology))
            {
                cout << "IMPOSSIBLE\n";
                return;
            }
        }
    }
    reverse(topology.begin(), topology.end());
    for (auto& node : topology) {
        cout << node << " ";
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
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

//Edit topological sort code because it can detect nodes
//Use path vector to store the path of the cycle

bool dfs(vc<int> graph[], vc<int>& state, int curr, vc<int> &path)
{
    if (state[curr] == 2) {
        return false;
    }
    else if (state[curr] == 1) {
        path.push_back(curr);
        return true;
    }

    state[curr] = 1;
    for (auto& node : graph[curr]) {
        if (dfs(graph, state, node, path)) {
            path.push_back(curr);
            return true;
        }
    }
    state[curr] = 2;
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

        graph[a].push_back(b);
    }

    vc<int> state(n+1, 0);
    for(int i=0; i<=n; ++i) {
        if(state[i] == 0) {
            vc<int> path;
            if(dfs(graph, state, i, path)) {
                reverse(path.begin(), path.end());
                //It could potentially have some extended nodes
                //before the start of the path. Start when it is the
                //same as the last node because the first and last are the same
                //in the path
                bool start_printing = false;
                for(int i = 0; i<(int)path.size(); ++i) {
                    if(start_printing) {
                        std::cout << path[i] << " ";
                    }
                    else {
                        if(path[i] == path[path.size()-1]) {
                            start_printing = true;
                            cout << path.size()-1-i+1 << endl;
                            std::cout << path[i] << " ";
                        }
                    }
                }
                std::cout << endl;
                return; 
            }
        }
    }

    cout << "IMPOSSIBLE" << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
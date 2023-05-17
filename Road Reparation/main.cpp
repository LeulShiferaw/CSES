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

//Basic minimum spanning tree construction

void solve()
{
    int n, m;
    cin >> n >> m;

    vc<pair<int, pr<int>>> edges;
    REP(i, 0, m) {
        int a, b, c;
        cin >> a >> b >> c;

        edges.push_back(make_pair(c, make_pair(a, b)));
    }

    sort(edges.begin(), edges.end());
    DSU st(n);
    ll ans = 0;
    int num_edges = 0;
    for(auto &edge : edges) {
        if(st.same(edge.second.first, edge.second.second)) {
            continue;
        }
        st.unite(edge.second.first, edge.second.second);
        ans += edge.first;
        num_edges++;
    }
    if(num_edges != n-1) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
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

constexpr ll INF = 1e17 + 1;

//The idea is simple just do bellman ford and find negative cyles
//Also keep a before vector to find the path
//In the before vector detect a repeating pattern because it may start
//with an element in the cycle, but it is connected to it.

void solve()
{
    int n, m;
    cin >> n >> m;

    vc<pair<int, pr<int>>> edgeList;
    vc<int> graph[n+1];
    REP(i, 0, m) {
        int a, b, c;
        cin >> a >> b >> c;

        edgeList.push_back({c, {a, b}});
        graph[a].push_back(b);
    }

    vc<ll> dis(n+1, INF);
    vc<int> before(n+1, -1);
    REP(i, 0, n-1) {
        for(auto &edge : edgeList) {
            if(dis[edge.second.first] + edge.first < dis[edge.second.second]) {
                dis[edge.second.second] = dis[edge.second.first] + edge.first;
                before[edge.second.second] = edge.second.first;
            } 
        }
    }

    bool ok = false;
    int node = 0;
    for(auto &edge : edgeList) { 
        if(dis[edge.second.first] + edge.first < dis[edge.second.second]) {
            ok = true;
            before[edge.second.second] = edge.second.first;
            node = edge.second.first;
        }
    }

    if(ok) {
        cout << "YES" << endl;
        int curr = node;
        set<pair<int, int>> new_nodes;
        new_nodes.insert({node, 0});
        int ind = 0;
        while(true) {
            curr = before[curr];
            auto found = new_nodes.lower_bound({curr, 0});
            if(found->first == curr) {
                node = curr;
                ind = found->second;
                break;
            }
            new_nodes.insert({curr, new_nodes.size()});
        }
        set<pair<int, int>> final_nodes;
        for(auto itr = new_nodes.begin(); itr != new_nodes.end(); ++itr)
            final_nodes.insert({itr->second, itr->first});

        vector<int> rev_nodes;
        for(auto itr = final_nodes.begin(); itr != final_nodes.end(); ++itr) {
            if(itr->first >= ind) {
                rev_nodes.push_back(itr->second);
            }
        }
        cout << node << " ";
        for(int i = rev_nodes.size()-1; i>=0; --i) {
            cout << rev_nodes[i] << " ";
        }
        cout << endl;
    }
    else {
        cout << "NO" << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
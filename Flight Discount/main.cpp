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

constexpr ll INF = 1e17+1;

vc<ll> dikstra(vc<pr<int>> graph[], int start, int n) {
    vc<ll> distance(n+1, INF);
    distance[start] = 0;
    vc<bool> used(n+1, false);
    std::priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    q.push(make_pair(0ll, start));
    while(!q.empty()) {
        auto dis = q.top().first;
        auto node = q.top().second;
        q.pop();
        if(used[node]) continue;
        used[node] = true;
        for(auto &neighbor : graph[node]) {
            if(dis + neighbor.second < distance[neighbor.first])
            {
                distance[neighbor.first] = dis + neighbor.second;
                q.push(make_pair(distance[neighbor.first], neighbor.first));
            }
        }
    }
    return distance;
}

//The idea is simple
//Find djikstra's from one then from N
//Now go through every edge between a and b and 
//find distance of a from one + b from N + dis(a, b)/2

void solve()
{
    int n, m;
    cin >> n >> m;

    vc<pr<int>> rGraph[n+1];
    vc<pr<int>> graph[n+1];
    vc<pair<ll, pr<int>>> edgeList;
    REP(i, 0, m) {
        int a, b, c;
        cin >> a >> b >> c;

        graph[a].PB(make_pair(b, c));
        rGraph[b].PB(make_pair(a, c));
        edgeList.push_back(make_pair(c, make_pair(a, b)));
    }

    auto fromOne = dikstra(graph, 1, n);
    auto fromN = dikstra(rGraph, n, n);
    
    ll ans = LLONG_MAX;
    for(auto &edge : edgeList) {
        if(edge.first/2 + fromOne[edge.second.first] + fromN[edge.second.second] < ans) {
            ans = edge.first/2 + fromOne[edge.second.first] + fromN[edge.second.second];
        }
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

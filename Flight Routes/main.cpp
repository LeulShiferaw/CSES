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
    vc<vc<bool>> used(n+1, vc<bool>(10, false));
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

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    vc<pr<int>> graph[n+1];
    REP(i, 0, m) {
        int a, b, c;
        cin >> a >> b >> c;

        graph[a].PB(make_pair(b, c));
    }

}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
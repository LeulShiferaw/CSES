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

constexpr int INF = 2e6+1;

vc<ll> djikstra(vc<pr<int>> graph[], int start, int n)
{
    vc<ll>   dis(n+1, INF);
    vc<bool> used(n+1, false);
    dis[1] = 0;
    std::priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push(make_pair(0ll, start));
    while(!pq.empty()) {
        auto dist  = pq.top().first;
        int  node = pq.top().second;
        pq.pop();
        if(used[node]) {
            continue;
        }
        used[node] = true;
        for(auto &element : graph[node]) {
            if(dist + element.second < dis[element.first])
            {
                dis[element.first] = dist + element.second;
                pq.push(make_pair(dis[element.first], element.first));
            }
        }
    }
    return dis;
}

//First check that you can travel any where from 1
//then, check if there is a path from all x to 1 
//to do this just reverse the graph and do djikstra's from 1
//If there is a path from 1 to anywhere and from anywhere to 1
//then there is a path from anywhere to anywhere
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<pr<int>> graph[n+1];
    vector<pr<int>> rgraph[n+1];
    REP(i, 0, m) {
        int a, b;
        cin >> a >> b;

        graph[a].PB(make_pair(b, 1));
        rgraph[b].PB(make_pair(a, 1));
    }

    auto res1 = djikstra(graph, 1, n);
    auto res2 = djikstra(rgraph, 1, n);

    for(int i = 1; i<=(int)res1.size(); ++i) {
        if(res1[i] == INF) {
            cout << "NO" << endl;
            cout << 1 << " " << i << endl;
            return;
        }
    }

    for(int i = 1; i<=(int)res2.size(); ++i) {
        if(res2[i] == INF) {
            cout << "NO" << endl;
            cout << i << " " << 1 << endl;
            return;
        }
    }

    cout << "YES" << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
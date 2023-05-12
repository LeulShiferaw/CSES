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

constexpr ll INF = 1e17 + 1;

vc<ll> djikstra(vv<pr<int>> &graph, int start, int n)
{
    vc<ll>   dis(n + 1, INF);
    vc<bool> used(n + 1, false);
    dis[1] = 0;
    std::priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push(make_pair(0ll, start));
    while (!pq.empty()) {
        auto dist = pq.top().first;
        int  node = pq.top().second;
        pq.pop();
        if (used[node]) {
            continue;
        }
        used[node] = true;
        for (auto& element : graph[node]) {
            if (dist + element.second < dis[element.first])
            {
                dis[element.first] = dist + element.second;
                pq.push(make_pair(dis[element.first], element.first));
            }
        }
    }
    return dis;
}

//Generate Shortest path graph
void generateSPG(vv<pr<int>> &rgraph, vv<pr<int>>& spgGraph, vv<pr<int>>& rspgGraph, const vc<ll>& dis, int n) {
    queue<int> q;
    q.push(n);
    vector<bool> used(n + 1, false);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        if (used[curr]) continue;
        used[curr] = true;
        for (auto& node : rgraph[curr]) {
            if (dis[curr] == dis[node.first] + node.second) {
                spgGraph[node.first].PB(make_pair(curr, node.second));
                rspgGraph[curr].PB(make_pair(node.first, node.second));
                q.push(node.first);
            }
        }
    }
}

int numSP(vv<pr<int>>& graph, vc<int>& dp, int curr)
{
    if (dp[curr] != -1) {
        return dp[curr];
    }

    int ans = 0;
    for (auto& node : graph[curr]) {
        ans += numSP(graph, dp, node.first);
        ans %= MOD;
    }
    dp[curr] = ans;
    return ans;
}

int minLen(vv<pr<int>>& graph, vc<int>& dp, int curr)
{
    if (dp[curr] != -1) {
        return dp[curr];
    }

    int ans = INT_MAX;
    for (auto& node : graph[curr]) {
        ans = min(ans, minLen(graph, dp, node.first));
    }
    dp[curr] = ans + 1;
    return dp[curr];
}

int maxLen(vv<pr<int>>& graph, vc<int>& dp, int curr)
{
    if (dp[curr] != -1) {
        return dp[curr];
    }

    int ans = 0;
    for (auto& node : graph[curr]) {
        ans = max(ans, maxLen(graph, dp, node.first));
    }
    dp[curr] = ans + 1;
    return dp[curr];
}

//Find the shortest path graph and apply DP on it

void solve()
{
    int n, m;
    cin >> n >> m;

    vv<pr<int>> graph(n + 1);
    vv<pr<int>> rgraph(n + 1);
    REP(i, 0, m) {
        int a, b, c;
        cin >> a >> b >> c;

        graph[a].push_back(make_pair(b, c));
        rgraph[b].PB(make_pair(a, c));
    }

    vc<ll> dis = djikstra(graph, 1, n);

    std::cout << dis[n] << " ";
    vv<pr<int>> spgGraph(n + 1); //Shortest path graph
    vv<pr<int>> rspgGraph(n + 1);//Reverse shortest path graph
    generateSPG(rgraph, spgGraph, rspgGraph, dis, n);

    vc<int> dpMany(n+1, -1); //size=n+1 and all are -1 for all three
    vc<int> dpMin(n+1, -1);
    vc<int> dpMax(n+1, -1);
    dpMany[1] = 1;
    dpMin[1] = 0;
    dpMax[1] = 0;
    std::cout << numSP(rspgGraph, dpMany, n) << " ";
    std::cout << minLen(rspgGraph, dpMin, n) << " ";
    std::cout << maxLen(rspgGraph, dpMax, n) << " ";
    std::cout << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
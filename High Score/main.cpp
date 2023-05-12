#include <bits/stdc++.h>
#include <bits/extc++.h>

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

/*
    The trick is to do bellman ford on the negated weights and find the shortest path.
    To detect a negative cycle only work on the edges when traversing from 1 -> n and from n -> 1 and also from n -> n
    Do this at the very end. But for everything before work on the whole edge list.
*/

bool dfs(vc<pr<int>> graph[], vc<int> &poss, vc<int> &occurr, int curr, int target, vc<pair<int, pr<int>>> &edgeList) {
    if(poss[curr] != -1) return poss[curr];
    if(occurr[curr] >= 2) return false;
    occurr[curr]++;

    bool ok = false;
    if(curr == target) return true;
    for(auto &node : graph[curr]) {
        if(dfs(graph, poss, occurr, node.first, target, edgeList)) {
            ok = true;
            edgeList.push_back({node.second, {curr, node.first}});
        }
    }
    poss[curr] = ok;
    occurr[curr]--;
    return ok;
}

bool dfs2(vc<pr<int>> graph[], vc<int> &poss, vc<int> &occurr, int curr, int target, vc<pair<int, pr<int>>> &edgeList) {
    if(poss[curr] != -1) return poss[curr];
    if(occurr[curr] >= 2) return false;
    occurr[curr]++;

    bool ok = false;
    for(auto &node : graph[curr]) {
        if(node.first == target) {
            ok = true;
            edgeList.PB({node.second, {curr, node.first}});
            continue;
        }
        if(dfs2(graph, poss, occurr, node.first, target, edgeList)) {
            ok = true;
            edgeList.push_back({node.second, {curr, node.first}});
        }
    }
    poss[curr] = ok;
    occurr[curr]--;
    return ok;
}

constexpr ll INF = 1e14 + 1;

void solve()
{
    int n, m;
    cin >> n >> m;

    vc<pr<int>> graph[n+1];
    vc<pair<int, pr<int>>> edgeList;
    vc<pair<int, pr<int>>> whole_edgeList;
    vc<int> occurr(n+1, 0);
    vc<int> poss(n+1, -1);
    REP(i, 0, m) {
        int a, b, x;
        cin >> a >> b >> x;

        bool ok = false;
        for (auto& node : graph[a]) {
            if (node.first == b) {
                node.second = min(node.second, -x);
                ok = true;
            }
        }

        if(!ok)
            graph[a].PB({ b, -x }); 
        whole_edgeList.push_back({-x, {a, b}});
    }

    dfs(graph, poss, occurr, 1, n, edgeList); 
    fill(occurr.begin(), occurr.end(), 0);  
    fill(poss.begin(), poss.end(), -1);  

    dfs(graph, poss, occurr, n, 1, edgeList);
    fill(occurr.begin(), occurr.end(), 0);  
    fill(poss.begin(), poss.end(), -1);  
    dfs2(graph, poss, occurr, n, n, edgeList);
    vc<ll> dis(n+1, INF);
    dis[1] = 0;
    bool ok = false;
    REP(i, 0, n) {
        ok = false;
        for(auto &edge : whole_edgeList) {
            if((dis[edge.second.first] + (ll)edge.first) < dis[edge.second.second]) {
                ok = true;
                dis[edge.second.second] = dis[edge.second.first] + (ll)edge.first;
            }
        }
        if(!ok) break;
    }
    ok = false;
    for(auto &edge : edgeList) {
        if((dis[edge.second.first] + (ll)edge.first) < dis[edge.second.second]) {
            ok = true;
            dis[edge.second.second] = dis[edge.second.first] + (ll)edge.first;
        }
    }
    if(ok) cout << -1 << endl;
    else {
        cout << -dis[n] << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
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

constexpr ll INF = 1e9 * 1e5 + 1; //Potential infinity for this problem

//Just do djikstra's algorithm
void solve()
{
    int n, m;
    cin >> n >> m;

    vc<pr<int>> graph[n+1];
    REP(i, 0, m) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].PB({c, b}); //Distance first then node index
    }

    vc<ll> dis(n+1, INF);
    vc<bool> used(n+1, false);
    dis[1] = 0;

    std::priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q; //Same here distance first then node index
    q.push({0, 1}); //Initially

    while(!q.empty()) {
        ll dist = q.top().first;//distance
        int pos = q.top().second;//node index
        if(used[pos]) {
            q.pop();
            continue;
        }

        used[pos] = true;
        for(auto &node : graph[pos]) {
            if(dist + node.first < dis[node.second]) {
                dis[node.second] = dist + node.first;
                q.push({dis[node.second], node.second});
            }
        }
        q.pop();
    }

    for(int i = 1; i<=n; ++i)
    {
        cout << dis[i] << " ";
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
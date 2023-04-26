#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for(int i = a; i<b; i++)
#define rREP(i, b, a) for(int i = b; i>=a; i--)

using indexed_set =  tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

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

constexpr int INF = 1000000+10;
void solve()
{
    int n, m;
    cin >> n >> m;

    int dis[n+1]; //Measure distance from 1
    bool used[n+1]; //Check traversed vertices
    vector<vi> graph(n+1); //Contains the full graph in adjacency list
    int before[n+1]; //Contains the element that comes before
    fill(dis, dis+n+1, INF); //Assign all distances as infinity
    fill(used, used+n+1, false); //Assign all used to false
    fill(before, before+n+1, 0); //All before are 0
    REP(i, 0, m)
    {
        int a, b;
        cin >> a >> b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    //Initialize for 1 
    dis[1] = 0;
    before[1] = -1;

    //Add the first set of edges
    std::priority_queue<pi, vector<pi>, greater<pi>> pq;
    for(auto &c : graph[1]) {
        dis[c] = 1;
        before[c] = 1;
        pq.push({dis[c], c});
    }

    //Do djikstra's algorithm
    while(!pq.empty())
    {
        auto nod = pq.top().second;
        if(used[nod]){
            pq.pop();
            continue;
        }
        for(auto &c : graph[nod])
        {
            if(pq.top().first + 1 < dis[c]) {
                dis[c] = pq.top().first + 1;
                before[c] = nod;
                pq.push({dis[c], c});
            }
        }
        used[nod] = true;
        pq.pop();
    }

    //If there is no connection to N
    if(dis[n] == INF) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    //Print number of vertices not edges
    cout << dis[n]+1 << "\n";

    //Retrace your steps using the before array
    vi nodes;
    int curr_node = n;
    while(true)
    {
        nodes.push_back(curr_node);
        if(before[curr_node] == -1) break;
        curr_node = before[curr_node];
    }

    //Reverse print the order
    rREP(i, nodes.size()-1, 0) {
        cout << nodes[i] << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
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
using vvi = vector<vi>;
using vvll = vector<vll>;

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

//The idea is very simple
//If there is a cycle then there is a cyclic path
//starting at one of the indexes
//Find that with dfs

//This function will do dfs on graph and set prev[nod] for the maximum
//cyclic length path
int dfs(const vvi& graph, bool used[], int target, int ind, vi &prev, int len, int &highest_node, int &highest_node_max)
{
    if (used[ind] && ind == target) return len;
    else if (used[ind]) return -1;
    used[ind] = true;

    auto res = -1;
    for (auto& nod : graph[ind])
    {
        auto temp = dfs(graph, used, target, nod, prev, len + 1, highest_node, highest_node_max);
        if (temp > res)
        {
            res = temp;
            if (nod == target) continue;
            prev[nod] = ind;
        }
    }
    if (res > highest_node_max)
    {
        highest_node_max = res;
        highest_node = ind;
    }
    return res;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<pi> edgeList;
    bool used[100000 + 1];
    fill(used, used + n + 1, false);
    vector<vector<int>> graph(n + 1);

    REP(i, 0, m)
    {
        int a, b;
        cin >> a >> b;

        edgeList.push_back({ a, b });
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    DSU st(n + 1);

    int start_edge = 0;
    bool possible = false;
    for (auto& edge : edgeList)
    {
        if (st.same(edge.first, edge.second)) {//If in same set
            possible = true;
            start_edge = edge.first;
            break;
        }

        st.unite(edge.first, edge.second);
    }

    if (!possible) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    vi prev(n+1, 0);//Prev array
    prev[start_edge] = -1;

    int hn = 0, hnmax = 0;//Highest node for getting the last node in the cycle
    dfs(graph, used, start_edge, start_edge, prev, 0, hn, hnmax);

    vi res;
    res.push_back(start_edge);//Starts with start edge
    while (true)//traverse the path using prev
    {
        res.push_back(hn);
        hn = prev[hn];
        if (hn == -1) break;
    }

    cout << res.size() << "\n";//Print the size of the longest path
    display(res);//Display the path itself
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
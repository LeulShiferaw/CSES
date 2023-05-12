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

constexpr ll INF = 1000 * 1e9 + 1;

//Simple! Just do floyd warshal algorithm on all
//Do the queries in O(1) time after that
//Be careful there could be more than one road in between
void solve()
{
    int n, m, q;
    cin >> n >> m >> q;

    vc<pr<int>> queries;
    vv<ll> adjMat(n+1, vc<ll>(n+1, INF));
    for(int i = 1; i<=n; ++i) adjMat[i][i] = 0;
    REP(i, 0, m) {
        int a, b, c;
        cin >> a >> b >> c;
        
        if(c < adjMat[a][b])
        {
            adjMat[a][b] = c;
            adjMat[b][a] = c;
        }
    }

    REP(i, 0, q) {
        int a, b;
        cin >> a >> b;
        queries.PB({a, b});
    }

    REP(k, 1, n+1) {
        REP(i, 1, n+1) {
            REP(j, 1, n+1) {
                adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);
            }
        }
    }

    for(auto &query : queries) {
        if(adjMat[query.first][query.second] == INF) cout << -1 << endl;
        else cout << adjMat[query.first][query.second] << endl;
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
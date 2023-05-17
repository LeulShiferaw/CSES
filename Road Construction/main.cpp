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

//Pretty easy with some thinking
//If they are not in the same set
//then decrease the number of components
//Also calculate their sum of elements and possibly set that as largest component

void solve()
{
    int n, m;
    cin >> n >> m;

    DSU st(n);
    int num_components = n;
    int largest_component = 1;
    vc<int>  num_elem(n+1, 1);
    vc<bool> used(n+1, false);
    vc<pr<int>> edges;
    REP(i, 0, m) {
        int a, b;
        cin >> a >> b;
        edges.push_back(make_pair(a, b));
    }

    for(auto &edge : edges) {
        int a = edge.first, b = edge.second;
        if(st.find(a) != st.find(b)) {
            num_components--;
            int x = num_elem[st.find(a)];
            int y = num_elem[st.find(b)];
            st.unite(a, b);
            num_elem[st.find(a)] = x+y;
            if(num_elem[st.find(a)] > largest_component) {
                largest_component = num_elem[st.find(a)];
            }
        }
        
        cout << num_components << " " << largest_component << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
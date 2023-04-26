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

void solve()
{
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
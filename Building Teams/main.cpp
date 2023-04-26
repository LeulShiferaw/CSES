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

//Simple solution using Bipartiteness check

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

//DFS - go through dfs style and check for mismatching colors
bool dfs(const vector<vector<int>> &graph, int color[], bool used[], int ind)
{
    if(used[ind]) return true;
    used[ind] = true; //Set current index as used
    for(auto &c : graph[ind])//Go through neighbors
    {
        if(color[c] == -1)//If they don't have a color, set a color
        {
            if(color[ind] == 1) color[c] = 2;//Opposite color
            else color[c] = 1;
        }
        else {
            if(color[c] == color[ind]) return false;//If there is a color and is same as yours then we have a mismatch
        }
        if(!dfs(graph, color, used, c))//If there is an error in the after next step
            return false;
    }
    return true;//If all goes well return true
}

void solve()
{
    int n, m;
    cin >> n >> m;

    bool used[n+1];
    int color[n+1];
    fill(color, color+n+1, -1);
    fill(used, used+n+1, false);
    vector<vector<int>> graph(n+1);
    REP(i, 0, m)
    {
        int a, b;
        cin >> a >> b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    //Go through all the nodes
    REP(i, 1, n+1)
    {
        if(color[i] == -1)//If they don't have a color, then this represents one component
        {
            color[i] = 1;//Set its color to 1 and check next
            if(!dfs(graph, color, used, i)) {//Do dfs and if it returns false it is IMPOSSIBLE
                cout << "IMPOSSIBLE\n";
                return;
            }
        }
    }

    //Print the colors
    REP(i, 1, n+1) {
        cout << color[i] << " ";
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
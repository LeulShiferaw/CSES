#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define all(x) (x).begin(), (x).end()
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define endl "\n"
#define REP(i, a, b) for(int i = a; i<b; i++)
#define rREP(i, b, a) for(int i = b; i>=a; i--)

template <typename T>
using indexed_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

constexpr int MAXN = 2e5+1;

int n;
vc<int> Tree[MAXN+1];
int numNodes[MAXN+1];

int dfs(int curr, int prev) {
    int res = 1;
    for(auto &x : Tree[curr]) {
        if(x == prev) continue;
        res += dfs(x, curr);      
    }
    numNodes[curr] = res;
    return res;
}

int findCentroid(int curr, int prev) {
    int mx = 0;
    int ind = 0;
    for(auto &x : Tree[curr]) {
        if(x == prev) continue;
        if(numNodes[x] > mx) {
            mx = numNodes[x];
            ind = x;
        }
    }
    if(mx <= floor(n/2) && (numNodes[1] - numNodes[curr]) <= floor(n/2)) {
        return curr;
    }
    else {
        if(ind == 0) return -1;
        return findCentroid(ind, curr);
    }
}

void solve()
{
    cin >> n;

    REP(i, 0, n-1) {
        int a, b;
        cin >> a >> b;

        Tree[a].pb(b);
        Tree[b].pb(a);
    }

    dfs(1, 0);
    cout << findCentroid(1, 0) << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
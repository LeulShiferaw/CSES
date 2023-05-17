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

vc<int> loops;
void dfs(vc<int> graph[], vc<bool> &used, int node) {
    if(used[node]) {
        loops.PB(node);
        return;
    }

    used[node] = true;
    for(auto &point : graph[node]) {
        dfs(graph, used, point);
    }
    used[node] = false;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    vc<int> graph[n+1];
    REP(i, 0, m) {
        int a, b;
        cin >> a >> b;

        graph[a].PB(b);
    }

    vc<int> dp(n+1, -1);
    vc<bool> used(n+1, false);
    for(int i = 1; i<=n; ++i) {
        if(!used[i]) {
            dfs(graph, used, i);
        }
    }

    vc<pr<int>> temp;
    for(int i = 1; i<=n; ++i) {
        temp.push_back(make_pair(dp[i], i));
    }
    sort(temp.begin(), temp.end());

    int nodeK = 1;
    dp[temp[0].second] = 1;
    for(int i =1; i<(int)temp.size(); ++i) {
        if((temp[i].first == -1) || (temp[i].first != temp[i-1].first)) {
            dp[temp[i].second] = ++nodeK;
        }
        else {
            dp[temp[i].second] = nodeK;
        }
    }

    std::cout << nodeK << endl;
    for(int i = 1;i<=n; ++i) {
        std::cout << dp[i] << " ";
    }
    std::cout << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
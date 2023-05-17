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


void dfs2(vc<int> &t, vc<int> &dp, vc<bool> &used, int node, int curr) {
    if(used[node]) return;
    used[node] = true;
    dp[node] += curr;
    dfs2(t, dp, used, t[node], curr+1);
}

int loop = -1;
int dfs(vc<int> &t, vc<int> &dp, vc<bool> &used, int node) {
    if(dp[node] != -1) return dp[node];

    if(used[node]) {
        loop = node; //We have to go over the loop and add the values from when the loop starts to it
        //This is because values that are added is the length after the node n to the end of loop
        //Not from beginning of loop
        return 0;
    }

    used[node] = true;
    auto res = dfs(t, dp, used, t[node]);
    dp[node] = res + 1;
    return dp[node];
}



void solve()
{
    int n;
    cin >> n;

    vc<int> t(n+1);
    for(int i = 1; i<=n; ++i) {
        cin >> t[i];
    }

    vc<int> dp(n+1, -1);
    vc<bool> used(n+1, false);
    vector<bool> used2(n+1, false);
    //Dfs everything while using a dp state
    for(int i = 1; i<=n; ++i) {
        if(!used[i])
        {
            dfs(t, dp, used, i);
            dfs2(t, dp, used2, loop, 0); //For adding the left overs in the loop
        }
    }

    for(int i = 1; i<=n; ++i) {
        cout << dp[i] << " ";
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
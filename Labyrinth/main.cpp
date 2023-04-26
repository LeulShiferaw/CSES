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

struct cmp {
    bool operator()(const pair<int, pi> &lhs, const pair<int, pi> &rhs) {
        return lhs.first > rhs.first;
    }
};

/*
    Do djikstra while also saving the previous value
    Then just retrace the steps.
    Make sure not to add to path like this: path = 'x' + path
    This takes too long. Instead do path += 'x'. Then print
    in reverse
*/

void solve()
{
    int n, m;
    cin >> n >> m;

    int INF = 1000000 + 10;

    vector<vi> dis(n, vi(m));
    vector<vector<bool>> used(n, vector<bool>(m));
    vector<vector<pi>> before(n, vector<pi>(m));
    vector<vector<char>> grid(n, vector<char>(m));
    std::priority_queue<pair<int, pi> , vector<pair<int, pi>>, cmp> pq;
    int ai = 0, aj = 0;
    int bi = 0, bj = 0;
    for(int i = 0; i<n; ++i)
    {
        for(int j=0; j<m; ++j)
        {
            before[i][j] = {0, 0};
            used[i][j] = false;
            cin >> grid[i][j];
            dis[i][j] = INF;
            if(grid[i][j] == 'A') {
                ai=i;
                aj=j;
            }
            else if(grid[i][j] == 'B') {
                bi = i;
                bj = j;
            }
        }
    }

    dis[ai][aj] = 0;
    before[ai][aj] = {-1, -1};
    if(ai-1 >= 0 && grid[ai-1][aj] != '#') {
        dis[ai-1][aj] = 1;
        before[ai-1][aj] = {ai, aj};
        pq.push({1, {ai-1, aj}});
    }
    if(ai+1 < n && grid[ai+1][aj] != '#') {
        dis[ai+1][aj] = 1;
        before[ai+1][aj] = {ai, aj};
        pq.push({1, {ai+1, aj}});
    }
    if(aj-1 >= 0 && grid[ai][aj-1] != '#') {
        dis[ai][aj-1] = 1;
        before[ai][aj-1] = {ai, aj};
        pq.push({1, {ai, aj-1}});
    }
    if(aj+1 < m && grid[ai][aj+1] != '#') {
        dis[ai][aj+1] = 1;
        before[ai][aj+1] = {ai, aj};
        pq.push({1, {ai, aj+1}});
    }

    used[ai][aj] = true;
    while(!pq.empty())
    {
        auto tp = pq.top();
        int tpi = tp.second.first, tpj = tp.second.second;
        if(used[tpi][tpj]) {
            pq.pop();
            continue;
        }
        if(tpi-1 >= 0 && grid[tpi-1][tpj] != '#') {
            if(dis[tpi][tpj] + 1 < dis[tpi-1][tpj]) {
                dis[tpi-1][tpj] = dis[tpi][tpj] + 1;
                before[tpi-1][tpj] = {tpi, tpj};
                pq.push({dis[tpi-1][tpj], {tpi-1, tpj}});
            }
        }
        if(tpi+1 < n && grid[tpi+1][tpj] != '#') {
            if(dis[tpi][tpj] + 1 < dis[tpi+1][tpj]) {
                dis[tpi+1][tpj] = dis[tpi][tpj] + 1;
                before[tpi+1][tpj] = {tpi, tpj};
                pq.push({dis[tpi+1][tpj], {tpi+1, tpj}});
            }
        }
        if(tpj-1 >= 0 && grid[tpi][tpj-1] != '#') {
            if(dis[tpi][tpj] + 1 < dis[tpi][tpj-1]){
                dis[tpi][tpj-1] = dis[tpi][tpj] + 1;
                before[tpi][tpj-1] = {tpi, tpj};
                pq.push({dis[tpi][tpj-1], {tpi, tpj-1}});
            }
        }
        if(tpj+1 < m && grid[tpi][tpj+1] != '#') {
            if(dis[tpi][tpj] + 1 < dis[tpi][tpj+1]){
                dis[tpi][tpj+1] = dis[tpi][tpj] + 1;
                before[tpi][tpj+1] = {tpi, tpj};
                pq.push({dis[tpi][tpj+1], {tpi, tpj+1}});
            }
        }
        used[tpi][tpj] = true;
    }
    if(dis[bi][bj] != INF) cout << "YES\n";
    else {
        cout << "NO\n";
        return;
    }
    cout << dis[bi][bj] << endl;
    /*
    REP(i, 0, n)
    {
        REP(j, 0, m) {
            if(dis[i][j] == INF) cout << " i ";
            else cout << " " << dis[i][j] << " ";
        }
        cout << endl;
    }
    REP(i, 0, n) {
        REP(j, 0, m) {
            cout << "(" << before[i][j].first << ", " << before[i][j].second << ") ";
        }
        cout << endl;
    }
    */
    string path = "";
    int x = bi, y = bj;
    while(true)
    {
        if(before[x][y].first == -1 && before[x][y].second == -1) break;
        if(before[x][y].first == x-1) {
            path += 'D';
        }
        else if(before[x][y].first == x+1) {
            path += 'U';
        }
        else if(before[x][y].second == y-1) {
            path += 'R';
        }
        else if(before[x][y].second == y+1) {
            path += 'L';
        }
        auto newx = before[x][y].first;
        auto newy = before[x][y].second;
        x = newx;
        y = newy;
    }
    for(int i = path.size()-1; i>=0; --i)
        cout << path[i];
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
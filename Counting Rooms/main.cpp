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

/*
    Very easy. Just iterate over it and do dfs. Don't repeat something you iterated over
*/

void dfs(vector<vector<char>> &grid, int x, int y)
{
    if(x < grid.size() && y < grid[0].size() && x >= 0 && y >= 0)
    {
        if(grid[x][y] == '#') return;
        else if(grid[x][y] == '.') grid[x][y] = '1';
        else if(grid[x][y] == '1') return;
        dfs(grid, x+1, y);
        dfs(grid, x-1, y);
        dfs(grid, x, y-1);
        dfs(grid, x, y+1);
    }
    return;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    REP(i, 0, n) {
        REP(j, 0, m) {
            cin >> grid[i][j];
        }
    }

    int num_rooms = 0;
    REP(i, 0, n) {
        REP(j, 0, m) {
            if(grid[i][j] == '#' || grid[i][j] == '1') continue;
            ++num_rooms;
            dfs(grid, i, j);
        }
    }
    cout << num_rooms << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
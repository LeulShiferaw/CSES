#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for(int i = a; i<b; i++)
#define rREP(i, b, a) for(int i = b; i>=a; i--)

using ll = long long;

template <typename T>
using pr = pair<T, T>;

template <typename T>
using vc = vector<T>;

template <typename T>
using vv = vector<vector<T>>;

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

/*
    Do BFS but also include the monsters
    Do the BFS of both
*/
void solve()
{
    int n, m;
    cin >> n >> m;

    int ax, ay;
    vv<char> grid(n, vc<char>(m));
    std::queue<pair<bool, pr<int>>> q; //For BFS
    vv<bool> used(grid.size(), vc<bool>(grid[0].size(), false));//For BFS
    vv<pr<int>> before(grid.size(), vc<pr<int>>(grid[0].size(), { -2, -2 }));//For BFS
    REP(i, 0, n)
    {
        REP(j, 0, m)
        {
            cin >> grid[i][j];
            if (grid[i][j] == 'A') {
                before[i][j] = { -1, -1 };
                ax = i; ay = j;
            }
            if (grid[i][j] == 'M') {
                q.push({ true, {i, j} });
            }
        }
    }

    q.push({ false, {ax, ay} }); //A's position must be added in at the end
    bool ok = false;
    pr<int> end = { -1, -1 };
    while (!q.empty())
    {
        bool monster = q.front().first;//Is it a monster
        pr<int> pos = q.front().second;//Current position
        if (pos.first < 0 || pos.first >= n || pos.second < 0 || pos.second >= m) { //Happens only for monsters
            if (!monster) {
                ok = true;
                end = { pos.first, pos.second };
                break;
            }
            else {
                q.pop();
                continue;
            }
        }
        if (used[pos.first][pos.second] || grid[pos.first][pos.second] == '#')
        {
            q.pop();
            continue;
        }

        if ((pos.first == 0) || (pos.first == (n - 1)) || (pos.second == 0) || (pos.second == (m - 1))) //Found solution if it is not monster
        {
            if (!monster) {
                ok = true;
                end = { pos.first, pos.second };
                break;
            }
        }

        used[pos.first][pos.second] = true;
        if (!monster) //If it is not a monster use add anything that is not a monster. So A can't move to a monster
        {
                if (pos.first - 1 >= 0 && grid[pos.first - 1][pos.second] == '.' && !used[pos.first-1][pos.second])
                {
                    before[pos.first - 1][pos.second] = { pos.first, pos.second };
                    q.push({ false, {pos.first - 1, pos.second} });
                }
                if (pos.first + 1 < n && grid[pos.first + 1][pos.second] == '.' && !used[pos.first+1][pos.second])
                {
                    before[pos.first + 1][pos.second] = { pos.first, pos.second };
                    q.push({ false, {pos.first + 1, pos.second} });
                }
                if (pos.second - 1 >= 0 && grid[pos.first][pos.second - 1] == '.' && !used[pos.first][pos.second-1])
                {
                    before[pos.first][pos.second - 1] = { pos.first, pos.second };
                    q.push({ false, {pos.first, pos.second - 1} });
                }
                if (pos.second + 1 < m && grid[pos.first][pos.second + 1] == '.' && !used[pos.first][pos.second+1])
                {
                    before[pos.first][pos.second + 1] = { pos.first, pos.second };
                    q.push({ false, {pos.first, pos.second + 1} });
                }
        }
        else {
            grid[pos.first][pos.second] = 'M';
            q.push({ true, {pos.first - 1, pos.second} });
            q.push({ true, {pos.first + 1, pos.second} });
            q.push({ true, {pos.first, pos.second - 1} });
            q.push({ true, {pos.first, pos.second + 1} });
        }
        q.pop();
    }

    if (ok) { //If there is a solution
        cout << "YES\n";
        vc<char> path;
        auto curr = end;
        while (true)
        {
            auto new_val = before[curr.first][curr.second];
            if (new_val == make_pair(-1, -1)) {
                break;
            }
            else if (new_val.first > curr.first) path.PB('U');
            else if (new_val.first < curr.first) path.PB('D');
            else if (new_val.second < curr.second) path.PB('R');
            else if (new_val.second > curr.second) path.PB('L');
            curr = new_val;
        }
        cout << path.size() << "\n";
        rREP(i, path.size() - 1, 0) {
            cout << path[i];
        }
        cout << "\n";
    }
    else cout << "NO\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
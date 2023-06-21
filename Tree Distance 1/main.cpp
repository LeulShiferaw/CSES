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

//First root at 1 and find all the longest path to leaf
int longestPath(vc<int> tree[], int curr, int prev, vc<pair<int, int>>& paths) {
    if (paths[curr] != make_pair(-1, -1))
        return paths[curr].first;

    if (prev == 0) {
        if (tree[curr].size() == 0) {
            paths[curr] = make_pair(0, 0);
            return 0;
        }
    }
    else if (tree[curr].size() - 1 == 0) {
        paths[curr] = make_pair(0, 0);
        return 0;
    }

    int node = -1;
    int longest = -1;
    for (auto& x : tree[curr]) {
        if (x == prev) continue;
        auto temp = longestPath(tree, x, curr, paths);
        if (temp > longest) {
            longest = temp;
            node = x;
        }
    }
    if (longest != -1) ++longest;
    paths[curr] = make_pair(longest, node);
    return longest;
}

//Now find the longest path and second longest path in any direction
void longestPath2(vc<int> tree[], int curr, vc<pair<int, int>>& longPaths, vc<pair<int, int>>& paths, vc<pair<int, int>>& paths2, vc<int>& parent) {
    //First calculate the second longest path downwards only, that will be val1
    auto val1 = make_pair(-1, -1);
    for (auto& x : tree[curr]) {
        if (x == parent[curr]) continue;
        if (x == longPaths[curr].second) continue;
        if (val1.first < longPaths[x].first) {
            val1.first = longPaths[x].first;
            val1.second = x;
        }
    }
    val1.first++;

    //val2 is the longest path upward
    auto val2 = make_pair(0, 0);
    if (parent[curr] == 0) { //If this is top there is no upward value
        val2 = make_pair(0, 0);
    }
    else {
        if (paths[parent[curr]].second == curr) {//else if best path from upward is this way
            val2.first = 1 + paths2[parent[curr]].first;//Get the 2nd best path from upward
            val2.second = parent[curr];//Make sure to adjust the new direction
        }
        else {
            val2.first = 1 + paths[parent[curr]].first;//otherwise, get the best path from upwards
            val2.second = parent[curr];
        }
    }

    paths[curr] = max(longPaths[curr], val2);//Best path is either the longest downward or the best upward
    if (paths[curr] == longPaths[curr]) {//If the path was downwards
        paths2[curr] = max(val1, val2);//The the 2nd best is either upwards or second downwards
    }
    else paths2[curr] = longPaths[curr];//Else if path was upwards then 2nd best is just the best downwards

    //Now repeat for the subtrees
    for (auto& x : tree[curr]) {
        if (x == parent[curr]) continue;
        longestPath2(tree, x, longPaths, paths, paths2, parent);
    }
}

void getParents(vc<int> tree[], int curr, int prev, vc<int>& parent) {
    parent[curr] = prev;
    for (auto& x : tree[curr]) {
        if (x == prev) continue;
        getParents(tree, x, curr, parent);
    }
}

void solve()
{
    int n;
    cin >> n;

    vc<int> tree[n+1];
    REP(i, 0, n - 1) {
        int a, b;
        cin >> a >> b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    vc<int> parent(n + 1, -1);
    parent[1] = 0;
    getParents(tree, 1, 0, parent);
    vc<pair<int, int>> paths(n + 1, make_pair(-1, -1));
    longestPath(tree, 1, 0, paths);
    vc<pair<int, int>> paths2(n + 1, make_pair(-1, -1));
    vc<pair<int, int>> paths3(n + 1, make_pair(-1, -1));
    longestPath2(tree, 1, paths, paths2, paths3, parent);
    for (int i = 1; i <= n; ++i) {
        std::cout << paths2[i].first << " ";
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
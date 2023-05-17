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

//Follow the book's algorithm
//Becareful succ must be declared as a global variable else it will be a seg fault

constexpr int logU = (int)log2(1e9) + 1;
int succ[(int)2e5+1][logU];

void solve()
{
    int n, q;
    cin >> n >> q;
    

    REP(i, 0, n) {
        cin >> succ[i+1][0];
    }

    //int sz = (int)log2(u) + 1;
    int sz = logU;
    for(int j = 1; j<sz; ++j) {
        REP(i, 1, n+1) {
            succ[i][j] = succ[succ[i][j-1]][j-1];
        }
    }

    REP(i, 0, q) {
        int x, k;
        cin >> x >> k;

        int ind = 0;
        int curr = x;
        while(k != 0) {
            if(k % 2 == 1) {
                curr = succ[curr][ind];
            }
            k = k >> 1;
            ++ind;
        }
        std::cout << curr << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
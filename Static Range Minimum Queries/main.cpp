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

class SparseTable {
    private:
        vv<int> table; 
    public:
        SparseTable(int n) {
            table.resize(n, vc<int>(floor(log2(n))+1));
        }

        void build(vc<int> &arr) {
            assert(arr.size() == table.size());
            //For (1 << 0)
            for(int i= 0; i<(int)table.size(); ++i) {
                table[i][0] = arr[i];
            }

            //For (1 << i) where i >= 1
            for(int i = 1; i<(int)table[0].size(); ++i) {
                for(int j = 0; j<(int)table.size()-(1 << i) + 1; ++j) {
                    table[j][i] = min(table[j][i-1], table[j+(1 << (i-1))][i-1]);
                }
            }
        }

        int minQuery(int a, int b) {
            int maxPow2 = floor(log2(b-a+1));
            return min(table[a][maxPow2], table[b-(1 << maxPow2)+1][maxPow2]);
        }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    vc<int> x(n);
    REP(i, 0, n) {
        cin >> x[i];
    }

    SparseTable spt(n);
    spt.build(x);
    REP(i, 0, q) {
        int a, b;
        cin >> a >> b;

        cout << spt.minQuery(a-1, b-1) << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
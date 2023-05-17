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

constexpr int logU = (int)log2(2e5+5) + 1;
int succ[(int)2e5+1][logU];

int findKthSucc(int x, int k) {
    int ind = 0;
    int curr = x;
    while(k != 0) {
        if(k % 2 == 1) {
            curr = succ[curr][ind];
        }
        k = k >> 1;
        ++ind;
    }
    return curr;
}

int findN(int a, int b, int s, int e)
{
    if(s > e) return -1;
    else if(s == e) {
        if(findKthSucc(a, s) == b) return s;
        else return -1;
    }

    int m = (s+e)/2;
    int valm = findKthSucc(a, m);
    if(valm != b) return findN(a, b, m+1, e);
    if(m <= s) return m;
    int valm1 = findKthSucc(a, m-1);
    if(valm1 == b) {
        return findN(a, b, s, m-1);
    }
    else {
        return m;
    }
}

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
        int a, b;
        cin >> a >> b;

        if(a == b) { 
            cout << 0 << endl;
            continue;
        }
        int temp = succ[b][0];
        succ[b][0] = b;
        /*
        for(int j = 1; j<sz; ++j) {
            REP(i, 1, n+1) {
                succ[i][j] = succ[succ[i][j-1]][j-1];
            }
        }
        */
        cout << findN(a, b, 1, n+1) << endl;

        succ[b][0] = temp;
        /*
        for(int j = 1; j<sz; ++j) {
            REP(i, 1, n+1) {
                succ[i][j] = succ[succ[i][j-1]][j-1];
            }
        }
        */
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
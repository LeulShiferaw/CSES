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

int hamDis(int a, int b) {
    return __builtin_popcount(a^b);
}

int convertToNum(const string &binNum) {
    int res = 0;
    int currPow = 1;
    for(int i = binNum.size()-1; i>=0; --i) {
        if(binNum[i] == '1') {
            res += currPow;
        }
        currPow*=2;
    }
    return res;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    int nums[n];
    for(int i = 0; i<n; ++i) {
        string temp;
        cin >> temp;

        nums[i] = convertToNum(temp);
    }

    int res = INT_MAX;
    for(int i = 0; i<n; ++i) {
        for(int j = i+1; j<n; ++j) {
            auto curr = hamDis(nums[i], nums[j]);
            if(curr < res) {
                res = curr;
            }
        }
    }
    cout << res << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
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

constexpr int MAXSIZE = 1e6+1;

int ans = 1;
int cnt[MAXSIZE+1];

void increment_fac(int x) {
    int siz = sqrt(x);
    for(int i=1; i<=siz; ++i) {
        if(x % i == 0) {
            ++cnt[i];
            if(i != (x/i)) {
                ++cnt[x/i];
            } 
            if(cnt[i] > 1) {
                if(i > ans) ans = i;
            }
            if(cnt[x/i] > 1) if((x/i) > ans) ans = x/i;
        }
    }
}

//Factorise every number and keep a count of the factors
//Find the greatest factor with a count of more than one
void solve()
{
    int n;
    cin >> n;

    REP(i, 0, n) {
        int temp;
        cin >> temp;

        increment_fac(temp);
    }
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
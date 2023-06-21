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

ll exp(int a, int b) {
    if(b == 0) return 1;
    if(b == 1) return a;

    if(b%2 == 0) {
        ll temp = exp(a, b/2);
        return (temp * temp) % MOD;
    }
    else return (a*exp(a, b-1)) % MOD;
}

ll exp2(int a, long long b) {
    if(b < MOD) return exp(a, b);
    return exp(a, b % (MOD-1));
}

int cnt[26];
void solve()
{
    string str;
    cin >> str;

    long long fac[str.size()+1];
    fac[0] = 1;
    for(int i = 1; i<=(int)str.size(); ++i) {
        fac[i] = (fac[i-1] * i) % MOD;
    }

    for(auto &c : str) {
        cnt[c-'a']++;
    }

    long long res = fac[str.size()];
    for(int i = 0; i<26; ++i) {
        if(cnt[i] > 1) {
            res *= exp(fac[cnt[i]], MOD-2);//Modular Multiplicative inverse
            res %= MOD;
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
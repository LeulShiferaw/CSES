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

//x^n = m (mod m) -> x^n(mod m-1) = m mod(m) //this is on the book
long long topExp(int a, int b) {
    if(b == 0) return 1;
    if(b == 1) return a % (MOD-1);

    long long res = 1;
    if(b%2 == 0) {
        auto temp = topExp(a, b/2);
        temp %= (MOD-1);
        res *= temp*temp;
        res %= (MOD-1);
    }
    else {
        auto temp = topExp(a, b-1);
        temp %= (MOD-1);
        res *= temp * a;
        res %= (MOD-1);
    }
    return res;
}

long long botExp(int a, int b) {
    if(b == 0) return 1;
    if(b == 1) return a%(MOD);

    long long res = 1;
    if(b%2 == 0) {
        auto temp = botExp(a, b/2);
        temp %= MOD;
        res *= temp * temp;
        res %= MOD;
    }
    else {
        auto temp = botExp(a, b-1);
        temp %= MOD;
        res *= temp * a;
        res %= MOD;
    }
    return res;
}

long long exp(int a, int b, int c) {
    auto top = topExp(b, c);
    return botExp(a, top);
}

void solve()
{
    int n;
    cin >> n;

    REP(i, 0, n) {
        int a, b, c;
        cin >> a >> b >> c;

        cout << exp(a, b, c) << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
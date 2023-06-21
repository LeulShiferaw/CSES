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

constexpr int MAXN = 1e6+1;
int cnt[MAXN+1];

//Modular exponentiation
long long exp(int a, int b) {
    if(b == 0) return 1;
    if(b == 1) return a;

    long long res = 1;
    if(b%2 == 0) {
        auto temp = exp(a, b/2);
        res = temp*temp;
    }
    else {
        auto temp = exp(a, b-1);
        res = temp*a;
    }
    res %= MOD;
    return res;
}

//Fermat's theorem
long long exp2(int a, long long b) {
    if(b < MOD) return exp(a, b);
    return exp2(a, b % (MOD-1)) % MOD;
}

void solve()
{
    int n;
    cin >> n;

    REP(i, 0, n) {
        int p, power;
        cin >> p >> power;

        cnt[p] = power;
    }

    long long sum = 1, num_div = 1, mul_div = 1;
    long long num_fac_prod = 1;
    for(int i = 2; i<MAXN; ++i) {
        if(cnt[i] != 0) {
            long long temp = exp(i, cnt[i]+1);//exp(i, cnt[i]+1)
            sum *= ((temp - 1)*exp(i-1, MOD-2))%MOD;//Don't forget (a/b) mod m = (a mod m) * (b^-1 mod m) the last part is the multiplicative inverse of b
            sum %= MOD;

            num_div *= cnt[i] + 1;
            num_div %= MOD;

            temp =  exp2(i, ((long long)cnt[i]*(cnt[i]+1))/2); //Use exp2 and make sure the inputs are long long
            mul_div *= (exp(mul_div, cnt[i])*exp(temp, num_fac_prod)) % MOD;//if you write out the steps you will find that this is correct
            mul_div %= MOD;
            num_fac_prod *= cnt[i]+1; //Calc the num_fac_prod afterwards
            num_fac_prod %= MOD-1;//Make sure to do MOD-1 instead because that is how you do exp(temp, num_fac_prod) using fermat's theorem of x^n mod m = x^(n mod (m-1)) mod m
        }
    }
    cout << num_div << " " << sum << " " << mul_div << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
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
int first_prime[MAXN+1];
int cnt[MAXN+1];

void extended_sieve() {
    first_prime[1] = 1;
    for(int i = 2; i<MAXN; ++i) {
        if(first_prime[i] != 0) continue;
        first_prime[i] = i;
        for(int j = i*i; j<MAXN; j+=i) {
            if(first_prime[i] == 0) first_prime[i] = i;
        }
    }
}

//One solution is to save the distince prime factors of each number using sieve
//Also have a count for the number of elements that have that number as a factor = O(n sqrt(n))
//Now go through the subset of the distinct prime factors and add for odd parity and subract for even parity the cnt[the product of the chosen prime factors]
void solve()
{
    int n;
    cin >> n;

    vc<int> x(n);
    for(int i = 0; i<n; ++i) cin >> x[i];

    extended_sieve();
    for(int i = 0; i<n; ++i) {
        cnt[first_prime[x[i]]]++;
    }
    int res = 0;
    for(int i = 0; i<n; ++i) {
        int num = x[i];
        if(num == 1) {
            res += n-1;
            continue;
        }
        int non_coprime = 0;
        for(int j=2; j*j<=num; ++j) {
            bool ok = false;
            while(num%j == 0) {
                ok = true;
                num/=2;
            }
            if(ok) {
                non_coprime += cnt[j];
            }
        }
        if(num > 1) non_coprime += cnt[num];
        res += n-non_coprime;
    }
    cout << res/2 << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
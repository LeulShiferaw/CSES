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

ll lcm(const ll &a, const ll &b) {
    ll res = a / gcd(a, b);
    res *= b;
    return res;
}

//Add all subsets that have parity odd and subtract all that have parity even
//res = multiples(a1) + multiples(a2) + ... multiples(ak) - multiples(a1, a2) ..  - multiples(ak, ak) + multiples(a1,a2,a3) .. 
//You can find the multiples(a1, a2, ..., ak) by getting their product and dividing n by it
//This is because they are prime. Their lcm is just their product
//So just traverse the subsets and increment if it is odd and decrement otherwise
void solve()
{
    int k;
    long long n;
    cin >> n >> k;

    vc<ll> a(k);
    REP(i, 0, k) {
        cin >> a[i];
    }

    long long res = 0;
    int MAXSUBSET = (1 << k);
    for(int i = 1; i<MAXSUBSET; ++i) {
        int x = i;
        if(__builtin_popcount(x) % 2 == 0) {
            long long prod = 1;
            long long val = n;
            for(int j = 0; x != 0; ++j, x/=2) {
                if(x % 2 == 1) {
                    if(a[j] > val) {
                        prod = 0;
                        break;
                    }    
                    else {
                        prod *= a[j];
                        val = n/prod;
                    }
                }
            }
            if(prod != 0) {
                res -= n/prod;
            }
        }
        else {
            long long prod = 1;
            long long val = n;
            for(int j = 0; x != 0; ++j, x/=2) {
                if(x % 2 == 1) {
                    if(a[j] > val) {
                        prod = 0;
                        break;
                    }    
                    else {
                        prod *= a[j];
                        val = n/prod;
                    }
                }
            }
            if(prod != 0) {
                res += n/prod;
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
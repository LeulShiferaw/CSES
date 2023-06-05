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

//Uses 0 indexing
class SegXorTree {
    public: 
        int n;
        vc<ll> tree;
        SegXorTree(int siz):n(siz) {
            tree.resize((1 << (int)ceil(log2(2*siz))), 0);
        }
        //n is the size of input
        //incase input is like size n+1
        void build(const vc<ll> &input) {
            int end = 2*n;
            for(int i=n; i<end; ++i) {
                tree[i] = input[i-n];
            }
            for(int i=n-1; i>=1; --i) {
                tree[i] = tree[2*i] xor tree[2*i + 1];
            }
        }
        ll exorSum(int a, int b) {
            --a; --b;
            a += n; b += n;
            ll res = 0;
            while(a<=b) {
                if(a % 2 == 1) res = res xor tree[a++];
                if(b % 2 == 0) res = res xor tree[b--];
                a/=2; b/=2;
            }
            return res;
        }
        void set(int k, int u) {
            update(k, u-tree[k-1+n]);
        }
        void update(int k, int x) {
            --k;
            k += n;
            tree[k] += x;
            for(k/=2; k>=1; k/=2) {
                tree[k] = tree[2*k] xor tree[2*k+1];
            }
        }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    vc<ll> x(n);
    REP(i, 0, n) {
        cin >> x[i];
    }

    SegXorTree segXorT(n);
    segXorT.build(x);
    REP(i, 0, q) {
        int a, b;
        cin >> a >> b;

        cout << segXorT.exorSum(a, b) << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
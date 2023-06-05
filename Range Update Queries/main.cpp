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
class SegTree {
    public: 
        int n;
        vc<ll> tree;
        SegTree(int siz):n(siz) {
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
                tree[i] = tree[2*i] + tree[2*i + 1];
            }
        }
        ll sum(int a, int b) {
            --a; --b;
            a += n; b += n;
            ll sum = 0;
            while(a <= b) {
                if(a % 2 == 1) {
                    sum += tree[a++];
                } if(b % 2 == 0) {
                    sum += tree[b--];
                }
                a /= 2; b /= 2;
            }
            return sum;
        }
        void set(int k, int u) {
            update(k, u-tree[k-1+n]);
        }
        void update(int k, int x) {
            --k;
            k += n;
            tree[k] += x;
            for(k/=2; k>=1; k/=2) {
                tree[k] = tree[2*k] + tree[2*k+1];
            }
        }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    vc<ll> x(n);
    for(int i =0; i<n; ++i) cin >> x[i];

    vc<ll> diff_arr(n);
    diff_arr[0] = x[0];
    for(int i = 1; i<n; ++i) {
        diff_arr[i] = x[i]-x[i-1];
    }

    SegTree segT(n);
    segT.build(diff_arr);
    REP(i, 0, q) {
        int choice;
        cin >> choice;
        if(choice == 1) {
            int a, b, u;
            cin >> a >> b >> u;

            segT.update(a, u);
            if((b+1) <= n) {
                segT.update(b+1, -u);
            }
        } else {
            int k;
            cin >> k;
            std::cout << segT.sum(1, k) << endl;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
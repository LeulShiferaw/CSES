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

template <typename T>
void display(const vector<pair<T, T>> &v) {
    for(const auto &x : v) cout << x.first << " ";
    cout << endl;
}

//Lazy Propagating maximum segment tree
class SegMaxTreeLazy{
    public: 
        int n;
        vc<pair<ll, ll>> tree;//Second is for lazy update
        SegMaxTreeLazy(int siz) {
            int nearPow2 = (1 << (int)ceil(log2(siz)));
            n = nearPow2;
            tree.resize(2*nearPow2, make_pair(0ll, 0ll));
        }
        ll get(int k) {
            return maximum(k, k, 1, 1, n);
        }
        //n is the size of input
        //incase input is like size n+1
        void build(const vc<ll> &input) {
            for(int i=0; i<(int)input.size(); ++i) {
                tree[n+i].first = input[i];
            }
            for(int i=n-1; i>=1; --i) {
                tree[i].first = max(tree[2*i].first, tree[2*i + 1].first);
            }
        }

        ll maximum(int a, int b, int k, int l, int r) {
            if(tree[k].second != 0) {
                tree[k].first += tree[k].second;
                if(l != r) {
                    tree[2*k].second += tree[k].second;
                    tree[2*k + 1].second += tree[k].second;
                }
                tree[k].second = 0;
            }
            if(b < l || a > r) {
                return -LLONG_MAX;
            }
            if(l >= a && r <= b) return tree[k].first;
            int m = (l+r)/2;
            return max(maximum(a, b, 2*k, l, m), maximum(a, b, 2*k + 1, m+1, r));
        }

        ll maximum(int a, int b) {
            return maximum(a, b, 1, 1, n);
        }

        void set(int k, int u) {
            range_update(k, k, u-get(k));
        }
        void range_update(int a, int b, ll x) {
            range_update(a, b, x, 1, 1, n);
        }
        void range_update(int a, int b, ll x, int k, int l, int r) {
            if(l > r) return;

            if(tree[k].second != 0) {
                tree[k].first += tree[k].second;
                if(l != r) {
                    tree[2*k].second += tree[k].second;
                    tree[2*k + 1].second += tree[k].second;
                }
                tree[k].second = 0;
            }

            if(a > r || b < l) return;

            if(l >= a && r <= b) {
                tree[k].first += x;
                if(l != r) {
                    tree[2*k].second += x;
                    tree[2*k+1].second += x;
                }
                return;
            }

            int m = (l+r)/2;
            range_update(a, b, x, 2*k, l, m);
            range_update(a, b, x, 2*k+1, m+1, r);
            if(l != r) {
                tree[k].first = max(tree[2*k].first, tree[2*k+1].first);
            }
        }
};

//Lazy Propagating maximum segment tree
class SegTreeLazy{
    public: 
        int n;
        vc<pair<ll, ll>> tree;//Second is for lazy update
        SegTreeLazy(int siz) {
            int nearPow2 = (1 << (int)ceil(log2(siz)));
            n = nearPow2;
            tree.resize(2*nearPow2, make_pair(0ll, 0ll));
        }
        ll get(int k) {
            return sum(k, k, 1, 1, n);
        }
        //n is the size of input
        //incase input is like size n+1
        void build(const vc<ll> &input) {
            for(int i=0; i<(int)input.size(); ++i) {
                tree[n+i].first = input[i];
            }
            for(int i=n-1; i>=1; --i) {
                tree[i].first = tree[2*i].first + tree[2*i + 1].first;
            }
        }

        ll sum(int a, int b, int k, int l, int r) {
            if(l > r) return 0;
            if(tree[k].second != 0) {
                tree[k].first += tree[k].second;
                if(l != r) {
                    tree[2*k].second += tree[k].second;
                    tree[2*k + 1].second += tree[k].second;
                }
                tree[k].second = 0;
            }
            if(b < l || a > r) {
                return 0;
            }
            if(l >= a && r <= b) return tree[k].first;
            int m = (l+r)/2;
            return sum(a, b, 2*k, l, m) +  sum(a, b, 2*k + 1, m+1, r);
        }

        ll sum(int a, int b) {
            if(a > b) return 0;
            return sum(a, b, 1, 1, n);
        }

        void set(int k, int u) {
            range_update(k, k, u-get(k));
        }
        void range_update(int a, int b, ll x) {
            range_update(a, b, x, 1, 1, n);
        }
        void range_update(int a, int b, ll x, int k, int l, int r) {
            if(l > r) return;

            if(tree[k].second != 0) {
                tree[k].first += tree[k].second;
                if(l != r) {
                    tree[2*k].second += tree[k].second;
                    tree[2*k + 1].second += tree[k].second;
                }
                tree[k].second = 0;
            }

            if(a > r || b < l) return;

            if(l >= a && r <= b) {
                tree[k].first += x;
                if(l != r) {
                    tree[2*k].second += x;
                    tree[2*k+1].second += x;
                }
                return;
            }

            int m = (l+r)/2;
            range_update(a, b, x, 2*k, l, m);
            range_update(a, b, x, 2*k+1, m+1, r);
            if(l != r) {
                tree[k].first = tree[2*k].first + tree[2*k+1].first;
            }
        }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    vc<ll> x(n);
    REP(i, 0, n) cin >> x[i];
    vc<ll> preSum(n);
    preSum[0] = x[0];
    for(int i=1; i<n; ++i) {
        preSum[i] = preSum[i-1] + x[i];
    }
    /*
    SegTreeLazy segT(n);
    segT.build(x);
    */

    SegMaxTreeLazy segMaxT(n);
    segMaxT.build(preSum);
    REP(i, 0, q) {
        int choice;
        cin >> choice;

        if(choice == 1) {
            int k;
            ll u;
            cin >> k >> u;

            //segT.set(k, u);
            segMaxT.range_update(k, n, u-x[k-1]);
            x[k-1] = u;
        } else {
            int a, b;
            cin >> a >> b;
            ll res = segMaxT.maximum(a, b);
            //if((a-1) >= 1) res -= segT.sum(1, a-1);
            if(a-1 >= 1) {
                res -= segMaxT.maximum(a-1, a-1);
            }
            res = max(0ll, res);
            std::cout << res << endl;
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
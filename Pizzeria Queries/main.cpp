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

class node {
    public:
        ll mx, mn, mulLazy, addLazy;
        node(ll a, ll b, ll c, ll d) :mx(a), mn(b), mulLazy(c), addLazy(d){};
};

//Lazy Propagating min and max segment tree with range multiply and add
class SegMinMaxTreeLazy{
    public: 
        int n;
        vc<node> tree;
        SegMinMaxTreeLazy(int siz) {
            int nearPow2 = (1 << (int)ceil(log2(siz)));
            n = nearPow2;
            tree.resize(2*nearPow2, node(LLONG_MIN, LLONG_MAX, 1, 0));
        }
        ll getMin(int k) {

        }
        ll getMax(int k) {

        }
        //n is the size of input
        //incase input is like size n+1
        void build(const vc<ll> &input) {
            for(int i=0; i<(int)input.size(); ++i) {
                tree[n+i].mx = input[i];
                tree[n+i].mn = input[i];
            }
            for(int i=n-1; i>=1; --i) {
                tree[i].mx = max(tree[2*i].mx, tree[2*i + 1].mx);
                tree[i].mn = min(tree[2*i].mn, tree[2*i + 1].mn);
            }
        }

        ll maximum(int a, int b, int k, int l, int r) {
            if(tree[k].addLazy != 0) {
                tree[k].mx += tree[k].addLazy;
                tree[k].mn += tree[k].addLazy;
                if(l != r) {
                    tree[2*k].addLazy += tree[k].addLazy;
                    tree[2*k + 1].addLazy += tree[k].addLazy;
                }
                tree[k].addLazy = 0;
            }
            if(tree[k].mulLazy != 1) {
                if(tree[k].mulLazy < 0) {
                    auto res1 = minimum(a, b);
                    auto res2 = maximum(a, b);
                    tree[k].mx = tree[k].mulLazy * res1;
                    tree[k].mn = tree[k].mulLazy * res2;
                }
                else {
                    tree[k].mx *= tree[k].mulLazy;
                    tree[k].mn *= tree[k].mulLazy;
                }

                if(l != r) {
                    tree[2*k].mulLazy *= tree[k].mulLazy;
                    tree[2*k + 1].mulLazy *= tree[k].mulLazy;
                }
                tree[k].mulLazy = 1;
            }

            if(b < l || a > r) {
                return -LLONG_MAX;
            }
            if(l >= a && r <= b) return tree[k].mx;
            int m = (l+r)/2;
            return max(maximum(a, b, 2*k, l, m), maximum(a, b, 2*k + 1, m+1, r));
        }

        ll maximum(int a, int b) {
            return maximum(a, b, 1, 1, n);
        }

        ll minimum(int a, int b, int k, int l, int r) {
            if(tree[k].addLazy != 0) {
                tree[k].mx += tree[k].addLazy;
                tree[k].mn += tree[k].addLazy;
                if(l != r) {
                    tree[2*k].addLazy += tree[k].addLazy;
                    tree[2*k + 1].addLazy += tree[k].addLazy;
                }
                tree[k].addLazy = 0;
            }
            if(tree[k].mulLazy != 1) {
                if(tree[k].mulLazy < 0) {
                    auto res1 = minimum(a, b);
                    auto res2 = maximum(a, b);
                    tree[k].mx = tree[k].mulLazy * res1;
                    tree[k].mn = tree[k].mulLazy * res2;
                }
                else {
                    tree[k].mx *= tree[k].mulLazy;
                    tree[k].mn *= tree[k].mulLazy;
                }
                if(l != r) {
                    tree[2*k].mulLazy *= tree[k].mulLazy;
                    tree[2*k + 1].mulLazy *= tree[k].mulLazy;
                }
                tree[k].mulLazy = 1;
            }

            if(b < l || a > r) {
                return LLONG_MAX;
            }
            if(l >= a && r <= b) return tree[k].mn;
            int m = (l+r)/2;
            return min(minimum(a, b, 2*k, l, m), minimum(a, b, 2*k + 1, m+1, r));
        }

        ll minimum(int a, int b) {
            return minimum(a, b, 1, 1, n);
        }

        /*
        void set(int k, int u) {
            range_update(k, k, u-get(k));
        }
        */
        void range_update_add(int a, int b, ll x) {
            range_update_add(a, b, x, 1, 1, n);
        }
        void range_update_add(int a, int b, ll x, int k, int l, int r) {
            if(l > r) return;

            if(tree[k].addLazy != 0) {
                tree[k].mx += tree[k].addLazy;
                tree[k].mn += tree[k].addLazy;
                if(l != r) {
                    tree[2*k].addLazy += tree[k].addLazy;
                    tree[2*k + 1].addLazy += tree[k].addLazy;
                }
                tree[k].addLazy = 0;
            }

            if(a > r || b < l) return;

            if(l >= a && r <= b) {
                tree[k].mx += x;
                tree[k].mn += x;
                if(l != r) {
                    tree[2*k].addLazy += x;
                    tree[2*k+1].addLazy += x;
                }
                return;
            }

            int m = (l+r)/2;
            range_update_add(a, b, x, 2*k, l, m);
            range_update_add(a, b, x, 2*k+1, m+1, r);
            if(l != r) {
                tree[k].mx = max(tree[2*k].mx, tree[2*k+1].mx);
                tree[k].mn = min(tree[2*k].mn, tree[2*k+1].mn);
            }
        }
        void range_update_mul(int a, int b, ll x) {
            range_update_mul(a, b, x, 1, 1, n);
        }
        void range_update_mul(int a, int b, ll x, int k, int l, int r) {
            if(l > r) return;

            if(tree[k].mulLazy != 1) {
                if(tree[k].mulLazy < 0) {
                    auto res1 = minimum(a, b);
                    auto res2 = maximum(a, b);
                    tree[k].mx = tree[k].mulLazy * res1;
                    tree[k].mn = tree[k].mulLazy * res2;
                }
                else {
                    tree[k].mx *= tree[k].mulLazy;
                    tree[k].mn *= tree[k].mulLazy;
                }
                if(l != r) {
                    tree[2*k].mulLazy *= tree[k].mulLazy;
                    tree[2*k + 1].mulLazy *= tree[k].mulLazy;
                }
                tree[k].mulLazy = 1;
            }

            if(a > r || b < l) return;

            if(l >= a && r <= b) {
                if(x < 0) {
                    auto res1 = minimum(a, b);
                    auto res2 = maximum(a, b);
                    tree[k].mx = x * res1;
                    tree[k].mn = x * res2;
                }
                else {
                    tree[k].mx *= x;
                    tree[k].mn *= x;
                }
                if(l != r) {
                    tree[2*k].mulLazy *= x;
                    tree[2*k+1].mulLazy *= x;
                }
                return;
            }

            int m = (l+r)/2;
            range_update_mul(a, b, x, 2*k, l, m);
            range_update_mul(a, b, x, 2*k+1, m+1, r);
            if(l != r) {
                tree[k].mx = max(tree[2*k].mx, tree[2*k+1].mx);
                tree[k].mn = min(tree[2*k].mn, tree[2*k+1].mn);
            }
        }
};

//Lazy Propagating maximum segment tree
class SegMinTreeLazy{
    public: 
        int n;
        vc<pair<ll, ll>> tree;//Second is for lazy update
        SegMinTreeLazy(int siz) {
            int nearPow2 = (1 << (int)ceil(log2(siz)));
            n = nearPow2;
            tree.resize(2*nearPow2, make_pair(0ll, 0ll));
        }
        ll get(int k) {
            return minimum(k, k, 1, 1, n);
        }
        //n is the size of input
        //incase input is like size n+1
        void build(const vc<ll> &input) {
            for(int i=0; i<(int)input.size(); ++i) {
                tree[n+i].first = input[i];
            }
            for(int i=n-1; i>=1; --i) {
                tree[i].first = min(tree[2*i].first, tree[2*i + 1].first);
            }
        }

        ll minimum(int a, int b, int k, int l, int r) {
            if(tree[k].second != 0) {
                tree[k].first += tree[k].second;
                if(l != r) {
                    tree[2*k].second += tree[k].second;
                    tree[2*k + 1].second += tree[k].second;
                }
                tree[k].second = 0;
            }
            if(b < l || a > r) {
                return LLONG_MAX;
            }
            if(l >= a && r <= b) return tree[k].first;
            int m = (l+r)/2;
            return min(minimum(a, b, 2*k, l, m), minimum(a, b, 2*k + 1, m+1, r));
        }

        ll minimum(int a, int b) {
            return minimum(a, b, 1, 1, n);
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
                tree[k].first = min(tree[2*k].first, tree[2*k+1].first);
            }
        }
};

//Add 1, 2, 3 ... n to p[i]
//Add n, n-1, ... 1 to p[i]
//The center it to zero by subtracting k
//and (n+1)-k respectively.
//The find min(min(k, n), min(1, k))

void solve()
{
    int n, q;
    std::cin >> n >> q;

    vc<ll> p(n);
    REP(i, 0, n) std::cin >> p[i];

    vc<ll> newP(n);
    REP(i, 0, n) newP[i] = p[i] + i + 1;

    vc<ll> rnewP(n);
    REP(i, 0, n) rnewP[i] = p[i] + n-i;

    SegMinTreeLazy segT(n);
    segT.build(newP);
    SegMinTreeLazy rsegT(n); //Reverse
    rsegT.build(rnewP);
    
    REP(i, 0, q) {
        int choice;
        cin >> choice;

        if(choice == 1) {
            int k, x;
            cin >> k >> x;

            segT.range_update(k, k, x-p[k-1]);
            rsegT.range_update(k, k, x-p[k-1]);
            p[k-1] = x;
        } else {
            int k;
            cin >> k;

            segT.range_update(1, n, -k);
            rsegT.range_update(1, n, -((n+1)-k));
            auto res = segT.minimum(k, n);
            res = min(res, rsegT.minimum(1, k));
            std::cout << res << endl;
            segT.range_update(1, n, k);
            rsegT.range_update(1, n, ((n+1)-k));
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
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

class Node {
public:
    ll z0, z1;
    Node(ll a, ll b) :z0(a), z1(b) {}
};

//Lazy Propagating maximum segment tree
class PolySegTreeLazy {
public:
    int n;
    vc<pair<ll, Node>> tree;//Second is for lazy update
    PolySegTreeLazy(int siz) {
        int nearPow2 = (1 << (int)ceil(log2(siz)));
        n = nearPow2;
        tree.resize(2 * nearPow2, make_pair(0ll, Node(0ll, 0ll)));
    }
    ll get(int k) {
        return sum(k, k, 1, 1, n);
    }
    //n is the size of input
    //incase input is like size n+1
    void build(const vc<ll>& input) {
        for (int i = 0; i < (int)input.size(); ++i) {
            tree[n + i].first = input[i];
        }
        for (int i = n - 1; i >= 1; --i) {
            tree[i].first = tree[2 * i].first + tree[2 * i + 1].first;
        }
    }

    void applyLazyUpdate(ll k, ll l, ll r) {
        int m = (r+l)/2;
        if(tree[k].second.z1 != 0) {
            tree[k].first += tree[k].second.z1*((r-l)*(r-l+1))/2 + tree[k].second.z0*(r-l+1);
            if(l != r) {
                tree[2*k].second.z1 += tree[k].second.z1;
                tree[2*k].second.z0 += tree[k].second.z0;
                tree[2*k + 1].second.z1 += tree[k].second.z1;
                tree[2*k + 1].second.z0 += tree[k].second.z0 + (m+1-l) * tree[k].second.z1; // I don't know why we are multiplying with z1
            }
            tree[k].second.z1 = 0;
            tree[k].second.z0 = 0;
        }
    }

    ll sum(ll a, ll b, ll k, ll l, ll r) {
        if (l > r) return 0;
        applyLazyUpdate(k, l, r);
        if((k/2) >= 1) { //This is very important code you need to update the parents
            tree[k/2].first = tree[2*(k/2)].first + tree[2*(k/2) + 1].first;
        }
        if (b < l || a > r) {
            return 0;
        }
        if (l >= a && r <= b) return tree[k].first;
        int m = (l + r) / 2;
        auto res = sum(a, b, 2*k, l, m) + sum(a, b, 2*k + 1, m+1, r);
        if(l != r) {
            tree[k].first = tree[2*k].first + tree[2*k + 1].first;
        }
        return res;
    }

    ll sum(int a, int b) {
        if (a > b) return 0;
        return sum(a, b, 1, 1, n);
    }

    void range_update_add(ll a, ll b) {
        range_update_add(a, b, 1ll, 1ll, n);
    }
    void range_update_add(ll a, ll b, ll k, ll l, ll r) {
        if (l > r) return;

        applyLazyUpdate(k, l, r);
        if((k/2) >= 1) { //This is very important code you need to update the parents
            tree[k/2].first = tree[2*(k/2)].first + tree[2*(k/2) + 1].first;
        }
        if (a > r || b < l) return;

        int m = (l + r) / 2;
        if (l >= a && r <= b) {
            tree[k].first += ((r-l)*(r-l+1))/2 + (l-a+1)*(r-l+1);
            if (l != r) {
                tree[2*k].second.z1++;
                tree[2*k].second.z0 += l-a+1;
                tree[2*k + 1].second.z1++;
                tree[2*k + 1].second.z0 += m-a+2;
            }
            return;
        }

        range_update_add(a, b, 2 * k, l, m);
        range_update_add(a, b, 2 * k + 1, m + 1, r);
        if (l != r) {
            tree[k].first = tree[2 * k].first + tree[2 * k + 1].first;
        }
    }
};

void solve()
{
    /*
    vc<ll> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SegTreeLazy tsegT(input.size());
    tsegT.build(input);
    cout << tsegT.sum(1, 10) << endl;
    tsegT.range_update_add(1, 3);
    tsegT.range_update_add(2, 4);
    tsegT.range_update_add(5, 7);
    cout << tsegT.sum(1, 10) << endl;
    REP(i, 0, (int)tsegT.tree.size()) tsegT.sum(i+1, i+1);
    for(int i = 0; i<(int)tsegT.tree.size(); ++i) {
        cout << tsegT.tree[i].first << " ";
    }
    cout << endl;
    for(int i = 0; i<(int)tsegT.tree.size(); ++i) {
        cout << tsegT.tree[i].second.z0 << "," << tsegT.tree[i].second.z1 << " ";
    }
    cout << endl;
    return;
    */
    int n, q;
    cin >> n >> q;

    vc<ll> t(n);
    REP(i, 0, n) cin >> t[i];

    PolySegTreeLazy segT(n);
    segT.build(t);
    /*
    int add = 23;
    ll res = 0;
    for(int i = 42; i<=51; ++i) {
        res += segT.sum(i, i);
        res += add;
        ++add;
    }
    cout << "res: " << res << endl;
    */

    REP(i, 0, q) {
        int choice;
        cin >> choice;

        int a, b;
        cin >> a >> b;

        if(choice == 1) {
            segT.range_update_add(a, b);
        } else {
            cout << segT.sum(a, b) << endl;
            /*
            if(i == 4) {
            int add = 23;
            ll res = 0;
            for(int i = 42; i<=51; ++i) {
                res += segT.sum(i, i);
                res += add;
                ++add;
            }
            cout << "res: " << res << endl;
            cout << "res: " << segT.sum(a, b) << endl;
            }
            */
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
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

class Node {
    public:
        ll m, l, r, s;//Max in range, from left, from right and total sum respectively
        Node(ll a, ll b, ll c, ll d) {
            m = a; l = b; r = c; s = d;
        }
};

constexpr ll INF = 1e13 + 1;

//Uses 0 indexing
class SegMaxTree {
    public: 
        int n;
        vc<Node> tree;
        SegMaxTree(int siz) {
            int nearPow2 = (1 << (int)ceil(log2(siz)));
            n = nearPow2;
            tree.resize(2*nearPow2, Node(-INF, -INF, -INF, -INF));
        }
        ll get(int k) {
            --k;
            return tree[n+k].m;
        }
        //n is the size of input
        //incase input is like size n+1
        void build(const vc<ll> &input) {
            for(int i=0; i<(int)input.size(); ++i) {
                tree[n+i].l = input[i];
                tree[n+i].m = input[i];
                tree[n+i].r = input[i];
                tree[n+i].s = input[i];
            }
            for(int i=n-1; i>=1; --i) {
                tree[i].s = tree[2*i].s + tree[2*i + 1].s;
                tree[i].l = max(tree[2*i].l, tree[2*i].s + tree[2*i+1].l);
                tree[i].r = max(tree[2*i+1].r, tree[2*i+1].s + tree[2*i].r);
                tree[i].m = max(tree[2*i].m, max(tree[2*i+1].m, tree[2*i].r + tree[2*i + 1].l));
            }
        }
        /*
        ll maximum(int a, int b) {
            --a; --b;
            a += n; b += n;
            ll res = -1;
            while(a<=b) {
                if(a % 2 == 1) res = max(res, tree[a++]);
                if(b % 2 == 0) res = max(res, tree[b--]);
                a/=2; b/=2;
            }
            return res;
        }
        */
       /*
        void set(int k, int u) {
            update(k, u-tree[k-1+n]);
        }
        */
        void update(int k, int x) {
            --k;
            k += n;
            tree[k].l += x;
            tree[k].r += x;
            tree[k].m += x;
            tree[k].s += x;
            for(k/=2; k>=1; k/=2) {
                tree[k].s = tree[2*k].s + tree[2*k + 1].s;
                tree[k].l = max(tree[2*k].l, tree[2*k].s + tree[2*k+1].l);
                tree[k].r = max(tree[2*k+1].r, tree[2*k+1].s + tree[2*k].r);
                tree[k].m = max(tree[2*k].m, max(tree[2*k+1].m, tree[2*k].r + tree[2*k + 1].l));
            }
        }
};

//Do the divide and conquer algorithm with the segment tree
void solve()
{
    int n, m;
    cin >>  n >> m; 

    vc<ll> x(n);
    REP(i, 0, n) {
        cin >> x[i];
    }
    SegMaxTree segT(n);
    segT.build(x);
    REP(i, 0, m) {
        int k, u;
        cin >> k >> u;
        segT.update(k, u-segT.get(k));
        cout << max(0ll, segT.tree[1].m) << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
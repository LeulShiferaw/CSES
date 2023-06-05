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
class SegMaxTree {
    public: 
        int n;
        vc<ll> tree;
        SegMaxTree(int siz) {
            int nearPow2 = (1 << (int)ceil(log2(siz)));
            n = nearPow2;
            tree.resize(2*nearPow2, 0);
        }
        ll get(int k) {
            --k;
            return tree[n+k];
        }
        //n is the size of input
        //incase input is like size n+1
        void build(const vc<ll> &input) {
            for(int i=0; i<(int)input.size(); ++i) {
                tree[n+i] = input[i];
            }
            for(int i=n-1; i>=1; --i) {
                tree[i] = max(tree[2*i], tree[2*i + 1]);
            }
        }
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
        void set(int k, int u) {
            update(k, u-tree[k-1+n]);
        }
        void update(int k, int x) {
            --k;
            k += n;
            tree[k] += x;
            for(k/=2; k>=1; k/=2) {
                tree[k] = max(tree[2*k], tree[2*k+1]);
            }
        }
};

int findGreater(SegMaxTree &segT, int target, int curr) {
    if(curr >= segT.n) {
        if(segT.tree[curr] >= target)
            return curr - segT.n + 1;
        return 0;
    }

    if(segT.tree[curr] < target) return 0;
    if(segT.tree[2*curr] >= target) return findGreater(segT, target, 2*curr);
    if(segT.tree[2*curr+1] >= target) return findGreater(segT, target, 2*curr + 1);
    return 0;
}

int findGreater2(SegMaxTree &segT, int s, int e, int target) {
    if(s == e) {
        if(segT.get(s) >= target) {
            return s;
        } else {
            return 0;
        }
    }
    int m = (s+e)/2;
    auto res1 = segT.maximum(s, m);
    auto res2 = segT.maximum(m+1, e);
    if(res1 >= target) {
        return findGreater2(segT, s, m, target);
    } else if(res2 >= target) {
        return findGreater2(segT, m+1, e, target);
    } else {
        return 0;
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;

    vc<ll> h(n);
    REP(i, 0, n) cin >> h[i];

    vc<ll> r(m);
    REP(i, 0, m) cin >> r[i];

    SegMaxTree segT(n);
    segT.build(h);  
    for(auto &room : r) {
        auto res = findGreater2(segT, 1, segT.n, room);
        if(res != 0) {
            segT.update(res, -room);
        }
        cout << res << " ";
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
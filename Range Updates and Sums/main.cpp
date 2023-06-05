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

using ll = long long;

template <typename T>
using pr = pair<T, T>;

template <typename T>
using vc = vector<T>;

template <typename T>
using vv = vector<vector<T>>;

constexpr int MOD = 1e9 + 7;

template <typename T>
void display(const vector<T>& v)
{
    for (const auto& x : v) cout << x << " ";
    cout << endl;
}

class Node {
public:
    ll add, chang;
    Node(ll a, ll b) :add(a), chang(b) {}
};

//Lazy Propagating maximum segment tree
class SegTreeLazy {
public:
    int n;
    vc<pair<ll, Node>> tree;//Second is for lazy update
    SegTreeLazy(int siz) {
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

    void applyLazyUpdate(int k, int l, int r) {
        if (tree[k].second.add != 0) {
            tree[k].first += (ll)(r - l + 1) * tree[k].second.add;
            if (l != r) {
                if (tree[2 * k].second.chang != 0) {
                    tree[2 * k].second.chang += tree[k].second.add;
                }
                else {
                    tree[2 * k].second.add += tree[k].second.add;
                }

                if (tree[2 * k + 1].second.chang != 0) {
                    tree[2 * k + 1].second.chang += tree[k].second.add;
                }
                else {
                    tree[2 * k + 1].second.add += tree[k].second.add;
                }
            }
            tree[k].second.add = 0;
        }
        if (tree[k].second.chang != 0) {
            tree[k].first = (ll)(r - l + 1) * tree[k].second.chang;
            if (l != r) {
                tree[2 * k].second.chang = tree[k].second.chang;
                tree[2 * k + 1].second.chang = tree[k].second.chang;
                tree[2 * k].second.add = 0;
                tree[2 * k + 1].second.add = 0;
            }
            tree[k].second.chang = 0;
        }
    }

    ll sum(int a, int b, int k, int l, int r) {
        if (l > r) return 0;
        if(tree[k].second.add != 0 && tree[k].second.chang != 0) {
            cout << "ERROR!" << endl;
        }
        
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

    void set(int k, int u) {
        range_update_add(k, k, u - get(k));
    }
    void range_update_add(int a, int b, ll x) {
        range_update_add(a, b, x, 1, 1, n);
    }
    void range_update_add(int a, int b, ll x, int k, int l, int r) {
        if (l > r) return;

        applyLazyUpdate(k, l, r);

        if (a > r || b < l) return;

        if (l >= a && r <= b) {
            tree[k].first += x * (ll)(r - l + 1);
            if (l != r) {
                if (tree[2 * k].second.chang != 0) {
                    tree[2 * k].second.chang += x;
                }
                else {
                    tree[2 * k].second.add += x;
                }

                if (tree[2 * k + 1].second.chang != 0) {
                    tree[2 * k + 1].second.chang += x;
                }
                else {
                    tree[2 * k + 1].second.add += x;
                }
            }
            return;
        }

        int m = (l + r) / 2;
        range_update_add(a, b, x, 2 * k, l, m);
        range_update_add(a, b, x, 2 * k + 1, m + 1, r);
        if (l != r) {
            tree[k].first = tree[2 * k].first + tree[2 * k + 1].first;
        }
    }
    void range_update_set(int a, int b, ll x) {
        range_update_set(a, b, x, 1, 1, n);
    }
    void range_update_set(int a, int b, ll x, int k, int l, int r) {
        if (l > r) return;

        applyLazyUpdate(k, l, r);
        
        if (a > r || b < l) return;

        if (l >= a && r <= b) {
            tree[k].first = (ll)(r - l + 1) * x;
            if (l != r) {
                tree[2 * k].second.chang = x;
                tree[2 * k + 1].second.chang = x;
                tree[2 * k].second.add = 0;
                tree[2 * k + 1].second.add = 0;
            }
            return;
        }

        int m = (l + r) / 2;
        range_update_set(a, b, x, 2 * k, l, m);
        range_update_set(a, b, x, 2 * k + 1, m + 1, r);
        if (l != r) {
            tree[k].first = tree[2 * k].first + tree[2 * k + 1].first;
        }
    }
};

void solve()
{
    /*
    vc<ll> input = {1, 2, 3, 4, 5, 6, 7, 8};
    SegTreeLazy segmentT(input.size());
    segmentT.build(input);
    cout << segmentT.sum(1, 8) << endl;
    segmentT.range_update_set(7, 8, 2);
    cout << segmentT.tree[1].first << endl;
    return;
    */
    int n, q;
    cin >> n >> q;

    vc<ll> t(n);
    REP(i, 0, n) cin >> t[i];

    SegTreeLazy segT(n);
    segT.build(t);

    REP(i, 0, q) {
        int choice;
        cin >> choice;

        if (choice == 1) {
            int a, b, x;
            cin >> a >> b >> x;

           segT.range_update_add(a, b, x);
        }
        else if (choice == 2) {
            int a, b, x;
            cin >> a >> b >> x;

            segT.range_update_set(a, b, x);
        }
        else {
            int a, b;
            cin >> a >> b;
            std::cout << segT.sum(a, b) << endl;
            /*
            if(i == 58) {
                REP(i, 0, (int)segT.tree.size()) {
                    cout << "(" << segT.tree[i].second.chang << ", " << segT.tree[i].second.add << "), ";
                }
                cout << endl;
                std::cout << "Ans1: " << segT.sum(a, b) << endl;
                REP(i, 1, n) {
                    segT.sum(i, i);
                }
                REP(i, segT.n, 2*segT.n) {
                    cout << i-segT.n + 1 << ": " << segT.tree[i].first << ", ";
                }
                cout << endl;
                cout << "Actual Answer: ";
                ll res = 0;
                for(int i = a; i<=b; ++i) {
                    res += segT.tree[segT.n + (i-1)].first;
                }
                cout << res << endl;
                cout << "Ans: " << segT.sum(a, b) << endl;
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
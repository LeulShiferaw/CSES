#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

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

//Uses 0 indexing
class SegTree {
public:
    int n;
    vc<ll> tree;
    SegTree(int siz) {
        int nearPow2 = (1 << (int)ceil(log2(siz)));
        n = nearPow2;
        tree.resize(2 * nearPow2, 0);
    }
    ll get(int k) {
        --k;
        return tree[n + k];
    }
    //n is the size of input
    //incase input is like size n+1
    void build(const vc<ll>& input) {
        for (int i = 0; i < (int)input.size(); ++i) {
            tree[n + i] = input[i];
        }
        for (int i = n - 1; i >= 1; --i) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }
    ll sum(int a, int b) {
        --a; --b;
        a += n; b += n;
        ll res = 0;
        while (a <= b) {
            if (a % 2 == 1) res = res + tree[a++];
            if (b % 2 == 0) res = res + tree[b--];
            a /= 2; b /= 2;
        }
        return res;
    }
    void set(int k, int u) {
        update(k, u - tree[k - 1 + n]);
    }
    void update(int k, int x) {
        --k;
        k += n;
        tree[k] += x;
        for (k /= 2; k >= 1; k /= 2) {
            tree[k] = tree[2 * k] + tree[2 * k + 1];
        }
    }
};

//2d segment tree. update01 only works for switching b/n 0 and 1
//Only works for nxn grids
class SegTree2D {
public:
    int n;
    vc<SegTree> tree;
    SegTree2D(int siz) {
        int nearPow2 = (1 << (int)ceil(log2(siz)));
        n = nearPow2;
        tree.resize(2 * nearPow2, SegTree(siz));
    }
    //Assuming input is nxn
    void build(const vc<vc<ll>>& input) {
        for (int i = 0; i < (int)input.size(); ++i) {
            tree[n + i].build(input[i]);
        }
        for (int i = n - 1; i >= 1; --i) {
            for (int j = 0; j < (int)tree[i].tree.size(); ++j) {
                tree[i].tree[j] = tree[2 * i].tree[j] + tree[2 * i + 1].tree[j];
            }
        }
    }

    ll sum(int a, int b, int c1, int c2) {
        --a; --b;
        a += n; b += n;
        ll res = 0;
        while (a <= b) {
            if (a % 2 == 1) {
                res += tree[a++].sum(c1, c2);
            }
            if (b % 2 == 0) {
                res += tree[b--].sum(c1, c2);
            }
            a /= 2; b /= 2;
        }
        return res;
    }

    void update01(int r, int c) {
        --r;
        r += n;
        int add = 0;
        if (tree[r].get(c) == 1) {
            add = -1;
        }
        else {
            add = 1;
        }
        tree[r].update(c, add);
        while (r >= 1) {
            r /= 2;
            tree[r].update(c, add);
        }
    }
    void update(int r, int c, int x) {
        --r;
        r += n;
        tree[r].update(c, x);
        for (r /= 2; r >= 1; r /= 2) {
            tree[r].update(c, x);
        }
    }
    void show() {
        for (int i = 1; i < (int)tree.size(); ++i) {
            display(tree[i].tree);
        }
    }
};

void solve()
{
    /*
    vc<vc<ll>> test = { {7, 6, 1, 6}, {8, 7, 5, 2}, {3, 9, 7, 1}, {8, 5, 3, 8} };
    SegTree2D testSeg(test.size());
    testSeg.build(test);
    testSeg.show();
    cout << endl;
    testSeg.update(1, 2, 3);
    testSeg.show();
    return;
    */
    int n, q;
    cin >> n >> q;

    vc<vc<ll>> grid(n, vc<ll>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c;
            cin >> c;
            if (c == '.') grid[i][j] = 0;
            else grid[i][j] = 1;
        }
    }

    SegTree2D segT(n);
    segT.build(grid);
    REP(i, 0, q) {
        int choice;
        cin >> choice;

        if (choice == 1) {
            int x, y;
            cin >> x >> y;
            
            segT.update01(x, y);
        }
        else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            cout << segT.sum(x1, x2, y1, y2) << endl;
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
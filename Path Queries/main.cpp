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

//Uses 0 indexing
class SegTree {
    public: 
        int n;
        vc<ll> tree;
        SegTree(int siz) {
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
                tree[i] = tree[2*i] + tree[2*i + 1];
            }
        }
        ll sum(int a, int b) {
            --a; --b;
            a += n; b += n;
            ll res = 0;
            while(a<=b) {
                if(a % 2 == 1) res = res + tree[a++];
                if(b % 2 == 0) res = res + tree[b--];
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
                tree[k] = tree[2*k] + tree[2*k+1];
            }
        }
};

constexpr int MAXN = 2e5+1;

vc<ll> v;
ll sum[MAXN+1];
int pos[MAXN+1];
int numNodes[MAXN+1];
vc<int> Tree[MAXN+1];
vc<int> dfsTrav;
vc<ll>  sumTrav;

int dfs(int curr, int prev) {
    if(prev == 0) sum[curr] = v[curr-1];
    else sum[curr] = sum[prev] + v[curr-1];
    sumTrav.push_back(sum[curr]);
    dfsTrav.push_back(curr);
    int res = 1;
    for(auto &x : Tree[curr]) {
        if(x == prev) continue;
        res += dfs(x, curr);
    }
    numNodes[curr] = res;
    return res;
}

void solve()
{
    int n, q;
    cin >> n >> q;

    v.resize(n);
    REP(i, 0, n){
        cin >> v[i];
    }
    

    REP(i, 0, n-1) {
        int a, b;
        cin >> a >> b;

        Tree[a].push_back(b);
        Tree[b].push_back(a);
    }
    //Do DFS
    dfs(1, 0);

    //Create difference array
    vc<ll> diffArr;
    diffArr.push_back(sumTrav[0]);
    for(int i = 1; i<n; ++i) {
        diffArr.push_back(sumTrav[i]-sumTrav[i-1]);
    }

    //Build Segment tree
    SegTree segT(n);
    segT.build(diffArr);

    //Calculate position of node in dfsTrav
    for(int i = 0; i<(int)dfsTrav.size(); ++i) {
        pos[dfsTrav[i]] = i+1;
    }
    REP(i, 0, q) {
        int choice;
        cin >> choice;

        if(choice == 1) {
            int s, x;
            cin >> s >> x;

            segT.update(pos[s], x-v[s-1]);
            if(pos[s]+numNodes[s] <= segT.n) {
                segT.update(pos[s] + numNodes[s], v[s-1]-x);
            }
            v[s-1] = x;
        }
        else {
            int s;
            cin >> s;

            cout << segT.sum(1, pos[s]) << endl;
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
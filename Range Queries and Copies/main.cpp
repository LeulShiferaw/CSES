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

//For problem Range Queries and Copies
//Data structure for Persistent Segment trees
//You still have to declare the vectore of Node* for the versions
//Also another vector that points to kth version because versions may not
//be ordered interms of the versions. When you change the value of kth version
//you aren't supposed to add a new version at the bottom you are supposed to
//change the current version. So use another vector to maintain the versions
//But when you change a new element you still add that as a new version.
class Node {
    public:
        int n;
        ll val;
        Node *left, *right;
        Node(ll a, Node *l, Node *r, int newN) :val(a), left(l), right(r), n(newN) {};
        ~Node() {
            destroy(this);
        }

        void build(vc<ll> &input) {
            int nearPow2 = (1 << (int)ceil(log2(input.size())));
            n = nearPow2;
            build(this, input, 1, nearPow2);
        }
        void build(Node *curr, vc<ll> &input, int l, int r) {
            if(l == r) {
                if(l > (int)input.size()) return;
                curr->val = input[l-1];
                return;
            }

            int m = (l+r)/2;
            curr->left = new Node(0, nullptr, nullptr, m-l+1);
            curr->right = new Node(0, nullptr, nullptr, r-m);
            build(curr->left, input, l, m);
            build(curr->right, input, m+1, r);
            curr->val = curr->left->val + curr->right->val;
        }
        void destroy() {
            destroy(this);
        }
        void destroy(Node *node) {
            if(node == nullptr) return;
            destroy(node->left);
            destroy(node->right);
            delete node;
            node = nullptr;
        }
        void display() {
            display(this);
        }
        void display(Node *node) {
            if(node == nullptr) return;
            if(node->left == nullptr && node->right == nullptr) {
                cout << node->val << " ";
                return;
            }
            cout << node->val << " ";
            display(node->left);
            display(node->right);
        }
        ll sum(int a, int b) {
            return sum(this, a, b, 1, n);
        }
        ll sum(Node *curr, int a, int b, int l, int r) {
            if(l >= a && r <= b) return curr->val;
            if(l > b || r < a) return 0;
            int m = (l+r)/2;
            return sum(curr->left, a, b, l, m) + sum(curr->right, a, b, m+1, r);
        }
        void updateSet(int k, int x) {
            updateSet(this, 1, n, k, x); 
        }
        void updateSet(Node *curr, int l, int r, int k, int x) {
            if(k < l || k > r || l > r) return;
            if(l == r) {
                curr->val = x;
                return;
            }

            int m = (l+r)/2;
            if(k <= m)  {
                updateSet(curr->left, l, m, k, x);
            }
            else {
                updateSet(curr->right, m+1, r, k, x);
            }
            curr->val = curr->left->val + curr->right->val;
        }
        
};

void updateNewVersion(Node *prev, Node *curr, int l, int r, int k, int x) {
    if(k < l || k > r || l > r) return;
    if(l == r) {
        curr->val = x;
        return;
    }

    int m = (l+r)/2;
    if(k <= m)  {
        curr->right = prev->right;
        curr->left = new Node(0, nullptr, nullptr, 0);
        updateNewVersion(prev->left, curr->left, l, m, k, x);
    }
    else {
        curr->left = prev->left;
        curr->right = new Node(0, nullptr, nullptr, 0);
        updateNewVersion(prev->right, curr->right, m+1, r, k, x);
    }
    curr->val = curr->left->val + curr->right->val;
}

void updateNewVersion(Node *prev, Node *curr, int k, int x) {
    curr->n = prev->n;
    updateNewVersion(prev, curr, 1, curr->n, k, x);
}

void solve()
{
    int n, q;
    cin >> n >> q;

    vc<ll> t(n);
    REP(i, 0, n) cin >> t[i];

    vc<Node*> roots;
    vc<Node*> versions;
    versions.push_back(new Node(0, nullptr, nullptr, 0));
    versions[0]->build(t);
    roots.push_back(nullptr);
    roots[0] = versions[0];
    REP(i, 0, q) {
        int choice;
        cin >> choice;

        if(choice == 1) {
            int k, a, x;
            cin >> k >> a >> x;

            versions.push_back(new Node(0, nullptr,nullptr, 0));
            updateNewVersion(roots[k-1], versions.back(), a, x);
            roots[k-1] = versions.back();
        } else if(choice == 2) {
            int k, a, b;
            cin >> k >> a >> b;

            cout << roots[k-1]->sum(a, b) << endl;
        } else {
            int k;
            cin >> k;

            roots.push_back(roots[k-1]);
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
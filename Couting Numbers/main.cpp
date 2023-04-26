#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for(int i = a; i<b; i++)
#define rREP(i, b, a) for(int i = b; i>=a; i--)

using indexed_set =  tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

constexpr int MOD = 1e9+7;

template <typename T>
void display(const vector<T> &v)
{
    for(const auto &x : v) cout << x << " ";
    cout << endl;
}

bool is_zero(const string &str)
{
    for(const char &c : str)
        if(c != '0') return false;
    if(str.size()-1 <= 1) return false;
    return true;
}

long long count(long long n)
{
    if(n < 0) return 0;
    string strN = to_string(n);
    if(strN.size() == 1) {
        return 1;
    }

    ll res = 0;
    int xn = strN[0]-'0';
    int xn1 = strN[0]-'0';
    bool has_rep = false;
    for(int i = 1; i<strN.size(); ++i)
    {
        xn = strN[i]-'0';
        xn1 = strN[i-1]-'0';
        int org_xn = xn;
        if(xn1 < xn) xn--;
        res += (ll)(xn) * (ll)pow(9, strN.size()-1-i);
        if(xn1 == org_xn) {
            has_rep = true;
            break;
        }
    }
    if(!has_rep) res++;
    return res;
}

int num_dig(ll n)
{
    return floor(log10(n)) + 1;
}

ll all_count(const ll &n)
{
    if(n < 0) return 0;
    string strN = to_string(n);
    if(strN.size() == 1) return n+1;

    ll x1 = strN[0]-'0';
    ll res = pow(9, strN.size()) -1;
    res /= 8;
    res += (x1-1) * pow(9, strN.size()-1);
    res += count(n);
    return res;
}

bool hasRep(const ll& n)
{
    string strN = to_string(n);
    for(int i = 1; i<strN.size(); ++i)
        if(strN[i] == strN[i-1]) return true;
    return false;
}

void solve()
{

    ll a, b;
    cin >> a >> b;
    //cout << a-1 << ": " << all_count(a-1) << ", " << count(a-1) << endl;
    cout << a << ": " << count(a) << endl;
    //cout << b << ": " << all_count(b) << ", " << count(b) << endl;
    //cout << all_count(b) - all_count(a-1) << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
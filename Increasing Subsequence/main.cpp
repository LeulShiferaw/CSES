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

/*
    GeekforGeeks has the solution on their website check for nlogn
    Try some examples by hand and see a pattern
    You will find that it is change the first one that is lower_bound of x[i] to x[i]
    if that lower_bound is end then add the element.
    This is because it can be added to the end of the previous element(previous to lower_bound that is).
    But we don't change the previous one because it may lead to another longer increasing subsequence
    But if we change the previous one then the next one will have similar number of elements
    because the previous one just got incremented. And the ending number will be less than the lower_bound's one.
    This would mean you have two numbers such that a < b and the number of elements is equal.
    In this case all you have to keep the smaller one not the larger one.
*/

void solve()
{
    int n;
    cin >> n;

    vi x(n);
    for(int i = 0; i<n; ++i) cin >> x[i];

    vi dp(n+1, 0);
    dp[0] = 0;

    int len = 1;
    dp[len] = x[0];
    for(int i = 1; i<n; ++i)
    {
        if(x[i] < dp[0]) dp[0] = x[i];
        else if(x[i] > dp[len]) {
            dp[++len] = x[i];
        }
        else {
            auto itr = lower_bound(dp.begin()+1, dp.begin()+len, x[i]);
            *itr = x[i];
        }
    }
    cout << len << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
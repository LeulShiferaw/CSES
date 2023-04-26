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
    Similar concept to increasing subsequence. This time only store the ending times and reward.
    First sort based on the ending times
    Then add each element sequentially
    When you add the elements, add only the extension
    which is the value that ends before the current one begins + the current value.
    Now when you add this. Delete any element with greater or equal ending times and lesser or equal value.
    Don't add if there is a lesser ending time with more or equal reward.
    Also don't add if there is an element that has similar ending times and more or equal reward value.
*/

void add(set<pll> &st, const pll &p)
{
    auto itr = st.lower_bound(p);
    if(itr != st.begin())
    {
        --itr;
        if(itr->second >= p.second) return;
        ++itr;
    }

    if(itr == st.end())
    {
        st.insert(p);
        return;
    }

    while(true)
    {
        if(itr->first == p.first && itr->second >= p.second) return;
        if(itr->second > p.second) break;
        auto temp = ++itr;
        --itr;
        st.erase(itr);
        itr = temp;
    }
    st.insert(p);
}

void solve()
{
    int n;
    cin >> n;

    vector<pair<pi, int>> abp(n);
    for(int i = 0; i<n; ++i) cin >> abp[i].first.first >> abp[i].first.second >> abp[i].second;

    sort(abp.begin(), abp.end(), [](const pair<pi, int> &p1, const pair<pi, int> &p2) {
        if(p1.first.second == p2.first.second) return p1.first.first < p2.first.first;
        else return p1.first.second < p2.first.second;
    });

    set<pll> ending_reward;
    ending_reward.insert(make_pair(abp[0].first.second, abp[0].second));

    ll res = abp[0].second;
    for(int i=1; i<n; ++i)
    {
        auto itr = ending_reward.lower_bound({abp[i].first.first, 0});
        if(itr == ending_reward.begin())
        {
            add(ending_reward, {abp[i].first.second, abp[i].second});
            res = max(res, (ll)abp[i].second);
        }
        else {
            --itr;
            add(ending_reward, {abp[i].first.second, abp[i].second + itr->second});
            res = max(res, (ll)abp[i].second + (ll)itr->second);
        }
    }
    cout << res << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
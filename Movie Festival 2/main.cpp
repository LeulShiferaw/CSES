#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

struct sort_pred {
    bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right) {
        if(left.second == right.second) return left.first < right.first;
        return left.second < right.second;
    }
};

template <typename T>
using indexed_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T>
using indexed_cust_set =  tree<T, null_type, sort_pred, rb_tree_tag, tree_order_statistics_node_update>;

auto comp = [](const pi &p1, const pi &p2)
                    {
                        if(p1.second == p2.second) return p1.first < p2.first;
                        return p1.second < p2.second;
                    };

void solve()
{
    int n, k;
    cin >> n >> k;

    
    set<pi> startingTimes;
    set<pi, decltype(comp)> endingTimes(comp);

    
    bool used[n];
    for(int i = 0; i<n; ++i)
    {
        used[i] = false;

        int a, b;
        cin >> a >> b;

        startingTimes.insert({a, b});
        endingTimes.insert({a, b});
    }

    for(auto itr = endingTimes.begin(); itr != endingTimes.end(); ++itr)
    {
        if(k <= 0) break;
        auto temp = startingTimes.find(make_pair(itr->first, itr->second));
        if(temp == startingTimes.end()) continue;

        --k;
        int lim = itr->second;
        startingTimes.erase(temp);
        while(true)
        {
            auto nxt = startingTimes.lower_bound(make_pair(lim, 0));
            if(nxt == startingTimes.end()) break;

            lim = nxt->second;
            startingTimes.erase(nxt);
        }
    }
    cout << endingTimes.size() - startingTimes.size() << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
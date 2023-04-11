#include <bits/stdc++.h>

using namespace std;

//Checks if p2 is to the right of p1
bool to_left(const pair<int, int>& p1, const pair<int, int>& p2)
{
    if (p2.second < p1.first) return false;
    if (p2.second <= p2.second) return false;
    return true;
}

//P1 contains P2
bool contains(const pair<int, int>& p1, const pair<int, int>& p2)
{
    if (p1.first <= p2.first && p1.second >= p2.second)
        return true;
    return false;
}

int fnd(const vector<pair<int, int>> &v, const pair<int, int> &x, int s, int e)
{
    if(e == s+1)
    {
        if(v[s] == x) return s;
        return -1;
    }
    if(s >= e) return -1;

    int m = (s+e)/2;
    if(v[m] == x)
    {
        if(m == e-1) return m;
        else if(v[m+1] == x) return fnd(v, x, m+1, e);
        return m;
    }
    else if(to_left(v[m], x)) return fnd(v, x, m+1, e);
    return fnd(v, x, s, m);
}

int fnd_lb_contains(const vector<pair<int, int>> &v, const pair<int, int> &x, int s, int e)
{
    if(e == s+1)
        return s;
    if(s >= e) return -1;

    int m = (s+e)/2;
    if(contains(x, v[m]))
    {
        if(m == s) return m;
        else if(contains(x, v[m-1])) return fnd_lb_contains(v, x, s, m);
        return m;
    }
    return 0;
}

void solve()
{
    int n;
    cin >> n;

    vector<pair<int, int>> ranges(n);
    for(int i =0; i<n; ++i) cin >> ranges[i].first >> ranges[i].second;

    auto og_ranges = ranges;
    sort(ranges.begin(), ranges.end());
    sort(ranges.begin(), ranges.end(), [](const pair<int, int> &p1, const pair<int, int> &p2){
        return contains(p2, p1); 
    });
    cout << endl;
    for(auto pr : ranges)
        cout << pr.first << " " << pr.second << endl;

    for(int i = 0; i<og_ranges.size(); ++i)
    {
        auto curr_ind = upper_bound(ranges.begin(), ranges.end(), og_ranges[i]);
        if(curr_ind == ranges.begin())
        {
            cout << "0 ";
            continue;
        }
        auto lb = lower_bound(ranges.begin(), curr_ind-1, make_pair(og_ranges[i].first, 0));
        if(lb == ranges.end() || lb == curr_ind)
        {
            cout << "0 ";
            continue;
        }
        cout << "curr_ind: " << curr_ind - ranges.begin() << ", lb: " << lb - ranges.begin() << endl;
        cout << (curr_ind-ranges.begin()) - (lb-ranges.begin()) << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
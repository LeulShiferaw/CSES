#include <bits/stdc++.h>

using namespace std;

vector<int> two_sum(const vector<pair<long long, int>> &vec, const long long &sum, int l, int r)
{
    while(true)
    {
        if(l >= r) break;
        if(vec[l].first + vec[r].first == sum)
        {
            return {l, r};
        }
        else if(vec[l].first + vec[r].first < sum)
        {
            ++l;
        }
        else --r; 
    }

    return {-1, -1};
}

vector<int> soln(const vector<pair<long long, int>> &vec, long long sum)
{
    if(vec.size() < 3)
        return {-1, -1, -1};
    for(int i = 0; i<vec.size()-2; ++i)
    {
        auto temp = sum-vec[i].first;
        if(temp < 0) break;
        auto temp1 = two_sum(vec, temp, i+1, vec.size()-1);
        if(temp1[0] == -1) continue;
        return {i, temp1[0], temp1[1]};
    }
    return {-1, -1, -1};
}

void solve()
{
    int n, x;
    cin >> n >> x;

    vector<pair<long long, int>> a(n);
    for(int i=0; i<n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }

    sort(a.begin(), a.end());

    if(n < 3)
    {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    auto res = soln(a, x);
    if(res[0] == -1)
    {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    vector<int> sorted_res = {a[res[0]].second+1, a[res[1]].second+1, a[res[2]].second+1};
    sort(sorted_res.begin(), sorted_res.end());
    for(int i =0; i<sorted_res.size(); ++i)
        cout << sorted_res[i] << " ";
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
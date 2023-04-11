#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n);
    vector<pair<int, int>> a_range(n); //Get the range of apartment desire
    for(int i = 0; i<n; ++i) cin >> a[i];
    for(int i = 0; i<n; ++i) a_range.push_back({a[i]-k, a[i]+k});//Get the range

    vector<int> b(m);//Get the prices
    for(int i = 0; i<m; ++i) cin >> b[i];

    sort(b.begin(), b.end());//Sort the prices in ascending order
    sort(a_range.begin(), a_range.end(), [](const pair<int, int> &lhs, const pair<int, int> &rhs){ //Sort the ranges using the ending price range
        if(lhs.second == rhs.second) return lhs.first < rhs.first;
        return lhs.second < rhs.second;
    });

    //Go through the elements in O(n+m) time
    int left = 0, right = 0, res = 0;
    while(true)
    {
        if(left == a_range.size() || right == b.size()) break;
        if(b[right] >= a_range[left].first && b[right] <= a_range[left].second)//If it's between the current range
        {
            ++res; ++left; ++right;
        }
        else if(b[right] < a_range[left].first)//If it is before
            ++right;
        else ++left;//If it is after
    }
    cout << res << endl;
    return 0;
}
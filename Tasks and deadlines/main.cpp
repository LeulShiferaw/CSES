#include <bits/stdc++.h>

using namespace std;

//Simple. Answer is in guide to CP
void solve()
{
    int n;
    cin >> n;

    vector<pair<long long, long long>> info(n);
    for(int i =0; i<n;++i) cin >> info[i].first >> info[i].second;

    sort(info.begin(), info.end());

    long long res = 0;
    long long curr = 0;
    for(auto pr : info)
    {
        curr += pr.first;
        res += pr.second - curr;
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
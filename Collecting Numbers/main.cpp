#include <bits/stdc++.h>

using namespace std;

/*
    Sort the numbers along with their original position.
    As long as the numbers are in ascending order they will eventually
    be taken out in one round.
    If they are decreasing then add one round for the previous increasing
    sequence. The rounds must start from 1 for the last sequence.
    It can also start from 0 and increment by one at the end.
*/
void solve()
{
    int n;
    cin >> n;

    vector<pair<int, int>> x(n);
    for(int i = 0; i<n; ++i)
    {
        cin >> x[i].first;
        x[i].second = i;
    }

    sort(x.begin(), x.end());

    int rounds = 1;
    for(int i = 1; i<x.size(); ++i)
    {
        if(x[i-1].second > x[i].second)
            ++rounds;
    }
    cout << rounds << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
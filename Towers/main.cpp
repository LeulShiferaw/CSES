#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;

    multiset<int> boards;//Multi set of boards
    vector<int> k(n);
    for(int i = 0; i<n; ++i)
        cin >> k[i];

    for(int i = 0; i<k.size(); ++i)
    {
        auto it = boards.upper_bound(k[i]);//Get the one right above the current element
        if(it == boards.end())
        {
            boards.insert(k[i]);
        }
        else {//When you place it on top it has effectively changed values. So erase the old value and add the new one
            boards.erase(it);
            boards.insert(k[i]);
        }
    }
    cout << boards.size() << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
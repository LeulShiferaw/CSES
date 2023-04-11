#include <bits/stdc++.h>

using namespace std;

/*
    Sort by putting into multiset
    Then greedily solve by getting the next one with starting time greater than the current ending time
    Remove current and assign same room in this loop
    Repeat loop while there are no elements left
*/
void solve()
{
    int n;
    cin >> n;

    vector<pair<int, int>> arr_dep(n);
    for(int i = 0; i<n; ++i) cin >> arr_dep[i].first >> arr_dep[i].second;

    vector<int> rooms(n, 0);
    multiset<pair<pair<int, int>, int>> times;
    for(int i = 0; i<n; ++i) times.insert(make_pair(make_pair(arr_dep[i].first, arr_dep[i].second), i));

    int num_rooms = 1;
    while(times.size() > 0)
    {
        auto curr = times.begin();
        rooms[curr->second] = num_rooms;
        while(true)
        {
            auto next = times.lower_bound(make_pair(make_pair(curr->first.second+1, 0), -1));
            if(next == times.end())
            {
                times.erase(curr);
                break;
            }
            
            times.erase(curr);
            curr = next;
            rooms[curr->second] = num_rooms;
        }
        ++num_rooms;
    }

    cout << num_rooms-1 << endl;
    for(int i = 0; i<n; ++i) cout << rooms[i] << " ";
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
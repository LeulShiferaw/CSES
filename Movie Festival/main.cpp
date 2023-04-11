#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<pair<int, int>> movies(n);
    for(int i = 0; i<n; ++i)
        cin >> movies[i].first >> movies[i].second; 

    //Sort based on the ending times
    sort(movies.begin(), movies.end(), [](const pair<int, int> &lhs, const pair<int, int> &rhs){
        if(lhs.second == rhs.second) return lhs.first < rhs.first;
        return lhs.second < rhs.second;
    });

    int lst = -1;
    int res = 0;
    //After sorting based on ending times, greedily get all movies that don't clash with the previous movie selected
    for(int i = 0; i<movies.size(); ++i)
    {
        if(lst == -1)
        {
            ++res;
            lst = movies[i].second;
        }
        else if(movies[i].first >= lst)
        {
            ++res;
            lst = movies[i].second;
        }
    }
    cout << res << endl;
    return 0;
}
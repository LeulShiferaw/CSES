#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    
    vector<int> arrival(n), leave(n);
    for(int i = 0; i<n; ++i)
    {
        cin >> arrival[i] >> leave[i];
    }

    sort(arrival.begin(), arrival.end());
    sort(leave.begin(), leave.end());

    int res = 0;
    int curr = 0;
    int left = 0, right = 0;
    while(true)
    {
        if(left >= arrival.size())
            break;
        if(arrival[left] < leave[right])
        {
            ++curr;
            ++left;
        }
        else if(arrival[left] > leave[right])
        {
            --curr;
            ++right;
        }
        else {
            ++left, ++right;
        }

        res = max(res, curr);
    }
    cout << res << endl;
    return 0;
}
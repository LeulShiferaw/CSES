#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, x;
    cin >> n >> x;

    vector<pair<int, int>> a(n);
    for(int i = 0; i<n; ++i)
    {
        cin >> a[i].first;
        a[i].second = i+1;
    }
    
    sort(a.begin(), a.end());

    int left = 0;
    int right = n-1;
    while(left < right)
    {
        if((long long)a[left].first + (long long)a[right].first == (long long)x)
        {
            if(a[left].second < a[right].second)
                cout << a[left].second << " " << a[right].second << endl;
            else cout << a[right].second << " " << a[left].second << endl;
            return 0;
        }
        else if((long long)a[left].first + (long long)a[right].first > (long long)x)
            --right;
        else ++left;
    }
    cout << "IMPOSSIBLE" << endl;
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<long long> x(n);
    for(int i=0; i<n; ++i)
    {
        cin >> x[i];
    }

    long long curr = x[0];
    long long sum = x[0];
    for(int i = 1; i<n; ++i)
    {
        if(curr < 0)
            curr = x[i];
        else 
            curr += x[i];
        sum = max(curr, sum); 
    }
    cout << sum << endl;
    return 0;
}
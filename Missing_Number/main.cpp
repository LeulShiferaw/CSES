#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n;
    cin >> n;

    long long total = (n*(n+1))/2;

    for(int i = 1; i<n; ++i)
    {
        int temp;
        cin >> temp;
        total -= temp;
    }

    cout << total << endl;
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long n;
    cin >> n;

    long long res = 1;
    for(long long i = 0; i<n; ++i) 
    {
        res *= 2;
        res %= 1000000000 + 7;
    }

    cout << res << endl;
    return 0;
}
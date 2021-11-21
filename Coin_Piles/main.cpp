#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    
    while(t--)
    {
        long long a, b;
        cin >> a >> b;

        if((a+b)%3 == 0 && abs(a-b) <= min(a, b))
            cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    return 0;
}
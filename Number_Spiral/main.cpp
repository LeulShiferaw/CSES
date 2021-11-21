#include <bits/stdc++.h>

using namespace std;

bool up(int n)
{
    if(n%2==0)
        return true;
    return false;
}

int main()
{
    int t;
    cin >> t;

    while(t--)
    {
        int x, y;
        cin >> y >> x;
        --y; --x;

        int n = max(x, y);
        long long val_n = (long long)n*(n+1) + 1LL;
        long long res = 0;
        if(x == n)
        {
            if(up(n))
                res = val_n + abs(y-n);
            else res = val_n - abs(y-n);
        }
        else if(y==n)
        {
            if(up(n))
                res = val_n - abs(x-n);
            else res = val_n + abs(x-n);
        }
        cout << res << endl;
    }
    return 0;
}
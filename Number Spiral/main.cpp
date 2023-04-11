#include <cmath>
#include <iostream>

using namespace std;

long long value(long long &n)
{
    return n*n - n +1;
}

int main()
{
    int t;
    cin >> t;

    while(t--)
    {
        long long y, x;
        cin >> y >> x;

        long long near_val = max(y, x);
        long long res = value(near_val);

        long long diff = abs(y-x);
        if(near_val % 2 == 0)
        {
            if(y > x)
                res += diff;
            else res -= diff;
        }
        else if(y > x) res -= diff;
        else res += diff;

        cout << res << endl;
    }
    return 0;
}
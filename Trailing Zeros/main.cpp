#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long n;
    cin >> n;

    int num5 = 0;
    long long curr_pow = 5;
    for(int i = 1; i<13; ++i)
    {
        if(n/curr_pow == 0)
            break;
        else num5 += n/curr_pow;
        curr_pow *= 5;
    }
    cout << num5 << endl;
}
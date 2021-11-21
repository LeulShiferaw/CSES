#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int main()
{
    long long n;
    cin >> n;

    cout << n;
    while(true)
    {
        if(n==1) break;

        if(n%2 == 0)
            n/=2;
        else n=3*n+1;

        cout << " " << n;
    }
    cout << endl;
    return 0;
}
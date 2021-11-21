#include <bits/stdc++.h>

using namespace std;

int diff(int s1, int s2)
{
    if(s1 == 1)
    {
        if(s2 == 2)
            return 3;
        else return 2;
    }
    else if(s1 == 2)
    {
        if(s2 == 1)
            return 3;
        else return 1;
    }
    else if(s2 == 1)
        return 2;
    else return 1;
}

void soln(int n, int s1, int s2)
{
    if(n == 1)
    {
        cout << s1 << " " << s2 << endl;
        return;
    }

    soln(n-1, s1, diff(s1, s2));
    cout << s1 << " " << s2 << endl;
    soln(n-1, diff(s1, s2), s2);
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    cout << pow(2, n) - 1 << endl;
    soln(n, 1, 3);
    return 0;
}
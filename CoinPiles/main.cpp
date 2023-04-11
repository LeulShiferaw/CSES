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

        //First 3 cases can be derived from the equations
        //4th case: Worst case scenario you remove just 1 from the smaller pile. 
        //If by doing that you are left with more elements in it than 
        //there were in the small pile there is too much of a gap. 
        //because it should be at most twice that pile b/c you have to remove 2 from the other pile.
        //Therefore their subtraction shouldn't be more that the small pile 

        if((a+b)%3 == 0 && (2*a-b)%3 == 0 && (2*b-a)%3 == 0 && abs(a-b) <= min(a, b))
        {
            cout << "YES\n";
        }
        else cout << "NO\n";
    }
    return 0;
}

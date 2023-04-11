#include <bits/stdc++.h>

using namespace std;

/*
    First, sort the input
    Now if we have for example 1, 1, 1, 1, 2, 9. 
    At first we have 0 -> 0 of the first n numbers. After adding 1
    we will have 0 -> 1, then 0 -> 2, then 0->3, then 0->4, then 0->6, then we get the answer to be 7, because adding 9 will create a gap
    If we had 0 -> curr already, and we add a new number new_val, then we have added
    new_val -> new_val + curr to the equation. If new_val is greater than curr + 1
    then there will be a gap and the next numbers (which are greater) will not fill it in.
    Otherwise, we have changed it to 0 -> new_val+curr
*/
void solve()
{
    int n;
    cin >> n;

    vector<long long> x(n);
    for(int i = 0; i<n; ++i)
    {
        cin >> x[i];
    }

    sort(x.begin(), x.end());
    long long curr = 0;
    for(int i = 0; i<x.size(); ++i)
    {
        if(x[i] > curr+1)
        {
            cout << curr+1 << endl;
            return;
        }
        else {
            curr = x[i] + curr;
        }
    }
    cout << curr+1 << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

//Maximum number of products with max width
long long max_products(const vector<long long> &k, long long max_width)
{
    long long res = 0;
    for(int i = 0; i<k.size(); ++i)
        res += max_width/k[i];

    return res;
}

//Binary search the correct width
//This takes log(n) * n, the second n is for checking the max products for each width
long long correct_width(const vector<long long> &k, const long long &t, long long s, long long e)
{
    if(s == e-1)
    {
        return s;
    }

    long long m = (s+e)/2;
    long long curr = max_products(k, m);
    if(curr == t)
    {
        if(m == s) return m;
        long long temp = max_products(k, m-1);
        if(temp < t) return m;
        return correct_width(k, t, s, m);
    }
    else if(curr > t)
    {
        if(m == s) return m;
        long long temp = max_products(k, m-1);
        if(temp > t) return correct_width(k, t, s, m);
        else if(temp == t) return m-1;
        return m;
    }

    return correct_width(k, t, m+1, e);
}

void solve()
{
    long long n, t;
    cin >> n >> t;

    vector<long long> k(n);
    long long mn = LLONG_MAX;
    for(int i = 0; i<n; ++i)
    {
        cin >> k[i];
        if(k[i] < mn) mn = k[i];
    }

    cout << correct_width(k, t, 1, mn*t+1) << endl;//min is 1 while max is minimum k[i] * number of products
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
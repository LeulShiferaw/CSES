/*
    Sort it and for each number using prefix sums
    calculate the sums before and after then get n*p[i] where n is the number of elements before or after
    Now it is sums[x]-n*p[i] or n*p[i]-sums[x] for each side
    Just add this up to get the total score for this value. Find minimum of the total scores
    It isn't really sums[x] that is just used for represent the value on the comments
*/
#include <bits/stdc++.h>

using namespace std;

long long sum(const vector<long long> &sums, int i, int j)
{
    if(j < i) return 0;
    if(i == j) return sums[i];
    if(i == 0) return sums[j];
    return sums[j]-sums[i-1];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<long long> p(n);
    vector<long long> sums(n);
    for(int i = 0; i<n; ++i)
        cin >> p[i];

    sort(p.begin(), p.end());

    long long curr_sum = 0;
    for(int i = 0; i<n; ++i)
    {
        curr_sum += p[i];
        sums[i] = curr_sum;
    }
    long long res = LLONG_MAX;
    for(int i = 0; i<p.size(); ++i)
    {
        long long curr = p[i]*i - sum(sums, 0, i-1) + sum(sums, i+1, n-1) - (n-i-1)*p[i];
        res = min(res, curr);
    }
    cout << res << endl;
    return 0;
}
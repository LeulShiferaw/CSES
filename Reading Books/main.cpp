#include <bits/stdc++.h>

using namespace std;

int getK(const vector<long long> &t)
{
    long long sum_left = 0;
    long long sum_right = 0;

    int l = -1, r = t.size();
    while(true)
    {
        if(l == r) return l;
        else if(l > r) return -1;

        if(sum_left == sum_right)
        {
            ++l, --r;
            sum_left += t[l];
            sum_right += t[r];
        }
        else if(sum_left < sum_right)
        {
            ++l;
            sum_left += t[l];
        }
        else if(sum_left > sum_right)
        {
            --r;
            sum_right += t[r];
        }
    }
    return -1;
}

long long sum(const vector<long long> &vec, int s, int e)
{
    long long res = 0;
    for(int i = s; i<e; ++i)
        res += vec[i];
    return res;
}

void solve()
{
    int n;
    cin >> n;

    vector<long long> t(n);
    for(int i = 0; i<n; ++i) cin >> t[i];

    sort(t.begin(), t.end());

    if(t[0] == t[t.size()-1])
    {
        cout <<  sum(t, 0, t.size()) << endl;
        return;
    }
    int ind = getK(t);
    cout << 2LL*sum(t, ind, t.size()) << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
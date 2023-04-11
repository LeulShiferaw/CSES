#include <bits/stdc++.h>

using namespace std;

/*Sliding window algorithm*/

int arr[10000][10000];
void solve()
{

    cout << arr[0][0] << " " << arr[100][100] << endl;
    return;

    long long n, k;
    cin >> n >> k;

    vector<long long> x(n);//input
    for(int i = 0; i<n; ++i) cin >> x[i];

    long long curr_k = 0;//Curr number of distinct values from l to r inclusive
    unordered_map<int, int> cnt;//Number of elements of a value in the current range [l,r]
    long long l = 0, r = 0;
    curr_k = 1;//Initially there is only one element
    cnt[x[0]] = 1;//There is only one of x[0]
    long long res = 0;
    while(true)
    {
        if(curr_k <= k)//If curr_k <= k
        {
            res += r-l+1ll;//Add all ranges starting form [l,r] and ending with r

            ++r;
            if(r >= x.size()) break;
            ++cnt[x[r]];
            if(cnt[x[r]] == 1) curr_k++;
        }
        else if(curr_k > k)//If we have too many remove the first
        {
            cnt[x[l]]--;
            if(cnt[x[l]] == 0) --curr_k;
            ++l;
        }
    }
    cout << res << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
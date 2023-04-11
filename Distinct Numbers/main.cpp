#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> nums(n);
    for(int i = 0; i<n; ++i) cin >> nums[i];

    sort(nums.begin(), nums.end());

    int res = 0;
    for(int i = 1; i<nums.size(); ++i)
    {
        if(nums[i] != nums[i-1])
            ++res;
    }
    ++res;
    cout << res << endl;
    return 0;
}
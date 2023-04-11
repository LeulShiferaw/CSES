#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<int> k(n);
    set<pair<int,int>> nums;
    for(int i = 0; i<n; ++i){
        cin >> k[i];
    }

    int res = 0;
    int curr_left = 0;//This is where the current subset starts
    for(int i = 0; i<k.size(); ++i)
    {
        auto it = nums.lower_bound({k[i], -1});//Find anything above or equal to k[i]
        if(it == nums.end() || it->first != k[i])//If nothing is found just add the current element to nums
        {
            nums.insert({k[i], i});
        }
        else if(it->second < curr_left)//If what was found was before the left element just remove it and add the current
        {
            nums.erase(it);
            nums.insert({k[i], i});
        }
        else {//If what you found was after curr_left
            curr_left = it->second + 1;//Extend curr_left to new value
            nums.erase(it);//Erase it
            nums.insert({k[i], i});//Add the current value
        }

        res = max(res, i-curr_left+1);//Always keep calculating difference between curr_left and i
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
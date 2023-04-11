#include <bits/stdc++.h>

using namespace std;

//Simulation
//Be carefull because you can only do ++it or --it
//And when you erase that iterator becomes invalid

void solve()
{
    int n, k;
    cin >> n >> k;

    set<int> nums;
    for(int i = 1; i<=n; ++i)
        nums.insert(i);

    auto pos = nums.begin();    
    int ind = 0;
    while(nums.size() > 0)
    {
        int adv = k%nums.size();
        ind = (ind + adv) % nums.size();

        auto it = nums.begin();
        advance(it, ind);

        auto temp = it;
        ++temp;
        cout << *it << " ";
        nums.erase(it);
        it = temp;
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
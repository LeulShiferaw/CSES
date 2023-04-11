#include <bits/stdc++.h>

using namespace std;

//Simulation
//Be carefull because you can only do ++it or --it
//And when you erase that iterator becomes invalid

void solve()
{
    int n;
    cin >> n;

    set<int> nums;
    for(int i = 1; i<=n; ++i)
        nums.insert(i);
    bool skip = true;
    while(nums.size() != 0)
    {
        if(nums.size() == 1)
        {
            cout << *nums.begin() << endl;
            nums.erase(nums.begin());
            break;
        }

        auto it = nums.begin();
        if(skip) ++it;//If we skip the first number
        for(;; it++)//Since you will do ++it by restoring it to the number next to it in the following code, just do ++it
        {
            cout << *it << endl;
         
            //Store before erasing
            auto temp = it;
            ++temp;
         
            nums.erase(it);//Erase it
         
            it = temp;//Restore the number next to the one you erased so already you did ++it

            if(it == nums.end())//If the current one is end
            {
                skip = true;
                break;
            }

            ++it;
            if(it == nums.end())//If the next one is end
            {
                --it; 
                skip = false;
                break;
            }
            --it;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
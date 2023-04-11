/*
    Very Complicated code!
*/
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<long long>;
using vpi = vector<pi>;

void solve()
{
    int n;
    cin >> n;

    vpi x(n); //Get the data store with index
    for(int i = 0; i<n; ++i) {
        cin >> x[i].first;
        x[i].second = i+1;
    }

    vi soln(n, 0);//This store the solution in the correct order because we are going to sort the data and go through it in that order. But eventually
    //have to display in the correct order

    sort(x.begin(), x.end());//Sort the data first on the value then on the index

    //This is for duplicates
    //Since we can't use a duplicate 
    //We have to make sure to add them only on the last round
    //toAdd will store the values to then
    //Since we are going through the data in sorted order
    //all we have to do is add all of it on the last value that is duplicated
    vector<bool> addNow(n, false);
    addNow[n-1] = true;
    for(int i = 0; i<n-1; ++i)
    {
        if(x[i].first != x[i+1].first)
        {
            addNow[i] = true;
        }
    }

    soln[x[0].second-1] = 0; //the first one has a solution of 0

    vpi toAdd;//store values that are duplicated. Only add when addNow is true, which is for the last element of the duplicated element
    //This works because the values are sorted

    set<pi> soFar;//Values so far. Which is to the left. It store the second element first and the first element second
    //That means we have sorted the elements to the left first on the index(which is the second element of x) then on their value(which is the first)
    //Now we can apply lower_bound to find the one right before our index
    if(addNow[0])//If we add the first one
        soFar.insert({x[0].second, x[0].first});
    else toAdd.push_back({x[0].second, x[0].first});//else add it to toAdd
    for(int i = 1; i<x.size(); ++i)//Go through all the element from second
    {
        toAdd.push_back({x[i].second, x[i].first});//Add value to toAdd
        auto prev = soFar.lower_bound({x[i].second, 0});
        if(prev == soFar.begin() || (prev == soFar.end() && soFar.size() == 0))
        {
            soln[x[i].second-1] = 0;
            if(addNow[i])
            {
                for(auto &pr : toAdd)
                    soFar.insert(pr);
                toAdd.clear();
            }
            continue;
        }
        --prev;
        soln[x[i].second-1] = prev->first;
        if(addNow[i])
        {
            for(auto &pr : toAdd)
                soFar.insert(pr);
            toAdd.clear();
        }
    }

    for(int i = 0; i<soln.size(); ++i)
        cout << soln[i] << " ";
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
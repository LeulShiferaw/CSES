#include <bits/stdc++.h>

using namespace std;

/*
    The question is wrong. The answer sometimes includes the traffic lights as well.
    It doesn't count only those that don't have traffic lights.
*/
void solve()
{
    int x, n;
    cin >> x >> n;

    vector<int> p(n);
    for(int i = 0; i<n; ++i)
        cin >> p[i];

    multiset<int> values;
    multiset<int> my_heap;
    my_heap.insert(x);
    for(int i = 0; i<p.size(); ++i)
    { 
        int left = 0, right = 0;
        auto it = values.upper_bound(p[i]);
        if(it == values.end())
        {
            if(values.size() == 0)
            {
                left = p[i];
                right = x-(p[i]);
            }
            else {
                right = x-(p[i]);
                --it;
                left = p[i]-*it;

            }
            values.insert(p[i]);
        }
        else {
            auto itr = values.begin();
            if(*itr == *it)
            {
                left = p[i];
                right = (*it) - p[i];//There should be another -1 on each of these operations because it can't count the traffic lights
            }
            else {
                right = *it - p[i];
                --it;
                left = p[i]-*it;
            }
            values.insert(p[i]);
        }

        //You found the left and right parts of the portion we are dissecting
        //First remove their sum, then add the parts
        auto temp = my_heap.find(left+right);
        if(temp != my_heap.end())
            my_heap.erase(temp);
        my_heap.insert(left);
        my_heap.insert(right);
        cout << *my_heap.rbegin() << endl;//Use rbegin to get the highest element, this way it can be used as a heap
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
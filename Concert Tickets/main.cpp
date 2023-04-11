#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    multiset<int> h;//Multiset for the concert ticket prices
    vector<int> t(m);

    for(int i = 0; i<n; ++i)
    {
        int temp;
        cin >> temp;
        h.insert(temp);
    }

    for(int i = 0; i<m; ++i)
    {
        cin >> t[i];
    }

    for(int i = 0; i<t.size(); ++i)//Go through all the max price announced by the customer
    {
        if(h.size() == 0)//If there are no more tickets available
        {
            cout << "-1 ";
            continue;
        }
        auto tck = h.lower_bound(t[i]);//Find the position that is >= t[i]
        if(tck == h.end())//If there are none
        {
            tck--;//Go to prev value
            cout << *tck << " ";   
            h.erase(tck);
        }
        else if((*tck) > t[i])//if the value is the greater one
        {
            if(tck == h.begin())//If this is the first element then there are none
            {
                cout << "-1 ";
            }
            else {//Else go to the prev value
                tck--;
                cout << *tck << " ";
                h.erase(tck);//Don't forget to remove the element from the tickets
            }
        }
        else {//Else if this is the value
            cout << *tck << " ";
            h.erase(tck);
        }
    }
    cout << endl;
    return 0;
}
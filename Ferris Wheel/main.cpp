#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, x;
    cin >> n >> x;

    //Use a multiset to keep all the elements. Side not everything is already sorted
    multiset<int> p;
    for(int i = 0; i<n; ++i){
        int temp;
        cin >> temp;
        p.insert(temp);
    } 

    int res = 0;
    while(true)
    {
        if(p.size() == 0)
            break;

        //Get the first element from the beginning
        auto it = p.begin();
        int first = *it;
        p.erase(it);

        if(p.size() == 0)//If it is empty then just add this student to a gondola and break
        {
            ++res;
            break;
        }

        //Find the first element or if that doesn't exist the first greater element.
        //If there no more greater elements then return p.end()
        auto nxt = p.lower_bound(abs(x-first)); 
        if(nxt == p.end())//If there are no greater elements
        {
            --nxt;//Get the first smaller one
            p.erase(nxt);//Erase it form multiset
            ++res;//Add to gondola
            continue;
        }

        int second = *nxt;
        if(second + first > x)//If the their sum is greater
        {
            if(nxt == p.begin())//If there are no smaller ones
            {
                ++res;//Add the first to gondola and don't erase the second one
            }
            else {//Erase the first one smaller than the greater element, and add both to gondola
                nxt--;
                p.erase(nxt);
                ++res;
            }
        }
        else {//if it is <=, then remove second element and add both to gondola
            p.erase(nxt);
            ++res;
        }
    }
    cout << res << endl;
    return 0;
}
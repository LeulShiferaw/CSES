/*
    Solved by sorting and using sparse tables for finding minimum and maximum in my algorithm
*/
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

//Checks if p2 is to the right of p1
bool to_left(const pair<int, int>& p1, const pair<int, int>& p2)
{
    if (p2.second < p1.first) return false;
    if (p2.second <= p2.second) return false;
    return true;
}

//P1 contains P2
bool contains(const pair<int, int>& p1, const pair<int, int>& p2)
{
    if (p1.first <= p2.first && p1.second >= p2.second)
        return true;
    return false;
}

//Get the minimum from s->e
pair<int, int> min_query(const vector<vector<pair<int, int>>> &SPT, int s, int e)
{
    int sz = (e-s);
    int lg2sz = log2(sz);
    return min(SPT[s][lg2sz], SPT[e-(1<<lg2sz)][lg2sz]);
}

//Get the maximum from s->e
pair<int, int> max_query(const vector<vector<pair<int, int>>> &SPT, int s, int e)
{
    int sz = (e-s);
    int lg2sz = log2(sz);
    return max(SPT[s][lg2sz], SPT[e-(1<<lg2sz)][lg2sz]);
}

void solve()
{
    int n;
    cin >> n;

    vector<pair<int, int>> ranges(n);
    const int lg2n = (int)log2(n) + 1;
    vector<vector<pair<int, int>>> min_SpT(n+1, vector<pair<int, int>>(lg2n));//For sparse table for finding minimum and maximum range queries
    vector<vector<pair<int, int>>> max_SpT(n+1, vector<pair<int, int>>(lg2n));
    for (int i = 0; i < n; ++i){
        cin >> ranges[i].first >> ranges[i].second;
    }

    auto original_ranges = ranges;
    sort(ranges.begin(), ranges.end());//Sort based on the first element first and then the second element

    /*
        Algorithm narrows down the search by finding a subset
        of elements based on the first element and then finding
        the maximum or minimum of the second element depending on the question for getting the 
        most likely result.
    */

    for(int i= 0; i<n; ++i)
    {
        min_SpT[i][0].first = ranges[i].second;
        min_SpT[i][0].second = i;
        max_SpT[i][0].first = ranges[i].second;
        max_SpT[i][0].second = i;
    }

    for(int j = 1; j<lg2n; ++j)
    {
        for(int i = 0; i<n; ++i)
        {
            int sec_part = i+(1<<(j-1));
            if(sec_part >= n) break;
            min_SpT[i][j] = min(min_SpT[i][j-1], min_SpT[sec_part][j-1]);
            max_SpT[i][j] = max(max_SpT[i][j-1], max_SpT[sec_part][j-1]);
        }
    }

    //Checks if there is an element contained by (a, b)
    //First check if there is another (a, b)
    //Then find lower_bound of (a, 0) and lower_bound of (b+1, 0)
    //Now find the element with the smallest second element in between
    //Don't forget you can't include (a, b) so do (a, 0) -> (a, b) and then
    //(a, b) + 1 to (b+1, 0)
    for (int i = 0; i < ranges.size(); ++i)
    {
        int a = original_ranges[i].first, b = original_ranges[i].second;
        auto pos_ab = lower_bound(ranges.begin(), ranges.end(), make_pair(a, b));

        ++pos_ab;
        if(pos_ab != ranges.end() && *pos_ab == make_pair(a, b))
        {
            cout << "1 ";
            continue;
        }
        --pos_ab;

        auto pos_ao = lower_bound(ranges.begin(), ranges.end(), make_pair(a, 0));
        auto pos_b10 = lower_bound(ranges.begin(), ranges.end(), make_pair(b+1, 0));
        if(pos_ao != pos_ab)
        {
            int ind = min_query(min_SpT, pos_ao-ranges.begin(), pos_ab-ranges.begin()).second;
            if(contains(original_ranges[i], ranges[ind]))
            {
                cout << "1 ";
                continue;
            }
        }

        if(pos_ab+1 != pos_b10)
        {
            int ind = min_query(min_SpT, pos_ab-ranges.begin()+1, ranges.size()).second;
            if(contains(original_ranges[i], ranges[ind]))
            {
                cout << "1 ";
                continue;
            }
        }
        cout << "0 ";
    }
    cout << endl;

    //Find an element that contains (a, b)
    //find lower_bound of(a+1, 0) and go from 0 -> that number
    //and this time find the maximum. Don't forget it can't include (a, b)
    //So do what you did before
    for (int i = 0; i < ranges.size(); ++i)
    {
        int a = original_ranges[i].first, b = original_ranges[i].second;
        auto pos_ab = lower_bound(ranges.begin(), ranges.end(), make_pair(a, b));

        ++pos_ab;
        if(pos_ab != ranges.end() && *pos_ab == make_pair(a, b))
        {
            cout << "1 ";
            continue;
        }
        --pos_ab;

        auto pos_a10 = lower_bound(ranges.begin(), ranges.end(), make_pair(a+1, 0));
        if(pos_ab != ranges.begin())
        {
            int ind = max_query(max_SpT, 0, pos_ab-ranges.begin()).second;
            if(contains(ranges[ind], original_ranges[i]))
            {
                cout << "1 ";
                continue;
            }
        }

        if(pos_ab+1 != pos_a10)
        {
            int ind = max_query(max_SpT, pos_ab-ranges.begin()+1, pos_a10-ranges.begin()).second;
            if(contains(ranges[ind], original_ranges[i]))
            {
                cout << "1 ";
                continue;
            }
        }
        cout << "0 ";
    }
    cout << endl;
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    srand(time(0));

    solve();
    
    //auto res = lower_bound(vec.begin(), vec.end(), make_pair(3, 3));
    //cout << res->first << ", " << res->second << endl;
    return 0;
}
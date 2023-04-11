#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);


    //If it has more than one odd numbered similar alphabets NO SOLUTION
    //else set the odd numbered one to mid and always keep adding half of the rest to left
//Finally reverse the left and get the right.

    string str;
    cin >> str;
    
    sort(str.begin(), str.end());
    int cnt = 1; 
    string mid = "";
    string left = "";
    bool has_odd = false;
    for(int i = 1; i<str.size(); ++i)
    {
        if(str[i] == str[i-1])
            ++cnt;
        else {
            if(cnt % 2 == 1)
            {
                if(has_odd)
                {
                    cout << "NO SOLUTION\n";
                    return 0;
                }
                else {
                    has_odd = true;
                    for(int j = 0; j<cnt; ++j)
                    {
                        mid += str[i-1];
                    }
                }
            }
            else {
                for(int j = 0; j<cnt/2; ++j)
                    left += str[i-1];
            }
            cnt = 1;
        }
    }
    if(cnt % 2 == 1)
    {
        if(has_odd)
        {
            cout << "NO SOLUTION\n";
            return 0;
        }
        else {
            has_odd = true;
            for(int j = 0; j<cnt; ++j)
            {
                mid += str[str.size()-1];
            }
        }
    }
    else {
        for(int j = 0; j<cnt/2; ++j)
            left += str[str.size()-1];
    }

    string right = left;
    reverse(right.begin(), right.end()); 
    string res = left + mid + right;
    cout << res << endl;
    return 0;
}
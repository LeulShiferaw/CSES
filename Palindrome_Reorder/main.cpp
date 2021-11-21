#include <bits/stdc++.h>

using namespace std;

string reverse(const string& str)
{
    string res = "";
    for(int i = str.size()-1; i>=0; --i)
        res += str[i];
    return res;
}

int main()
{
    string str;
    cin >> str;

    sort(str.begin(), str.end());

    string mid = "";
    string curr = "";
    string res = "";
    for(int i = 0; i<str.size(); ++i)
    {
        if(i == 0 || str[i] == str[i-1])
            curr += str[i];
        else if(str[i] != str[i-1])
        {
            if(curr.size() % 2 == 0)
            {
                for(int j = 0; j<curr.size()/2; ++j)
                    res += curr[j];
                curr = str[i];
            }
            else if(mid == "")
            {
                mid = curr;
                curr = str[i];
            }
            else 
            {
                cout << "NO SOLUTION" << endl;
                return 0;
            }
        }
    }
    
    if(curr.size() % 2 == 0)
    {
        for(int j = 0; j<curr.size()/2; ++j)
            res += curr[j];
    }
    else if(mid == "")
        mid = curr;
    else 
    {
        cout << "NO SOLUTION" << endl;
        return 0;
    }

    res = res + mid + reverse(res);
    cout << res << endl;

    return 0;
}
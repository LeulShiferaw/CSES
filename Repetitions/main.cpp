#include <string>
#include <iostream>

using namespace std;

int main()
{
    string str;
    cin >> str;

    int max_len = 1;
    int curr = str[0];
    int curr_len = 1;
    for(int i = 1; i<str.size(); ++i)
    {
        if(str[i] == str[i-1])
        {
            ++curr_len;
        }
        else if(curr_len > max_len)
        {
            max_len = curr_len;
            curr_len = 1;
            curr = str[i];
        }
        else 
        {
            curr_len = 1;
            curr = str[i];
        }
    }

    if(curr_len > max_len)
    {
        max_len = curr_len;
        curr_len = 0;
    }

    cout << max_len << endl;
    return 0;
}
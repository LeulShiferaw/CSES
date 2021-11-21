#include <bits/stdc++.h>

using namespace std;

vector<string> gray_code(const int &n)
{
    vector<string> res;
    if(n == 1)
    {
        res.push_back("0");
        res.push_back("1");
        return res;
    }

    auto prev = gray_code(n-1);
    for(int i = 0; i<prev.size(); ++i)
        res.push_back("0" + prev[i]);
    for(int i = prev.size()-1; i>=0; --i)
        res.push_back("1" + prev[i]);
    return res;
}

void display(const vector<string> &vec)
{
    for(string str : vec)
        cout << str << endl;
}

int main()
{
    int n;
    cin >> n;

    display(gray_code(n));
    return 0;
}
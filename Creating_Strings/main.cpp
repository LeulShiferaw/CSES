#include <bits/stdc++.h>

using namespace std;

set<string> unique_perm(string str)
{
    set<string> res;
    do
    {
        res.insert(str);
    }while(next_permutation(str.begin(), str.end()));
    return res;
}

int fac[8+5];
int main()
{
    int temp = 1;
    for(int i = 1; i<=8; ++i)
    {
        temp *= i;
        fac[i] = temp;
    }

    string str;
    cin >> str;

    sort(str.begin(), str.end());

    auto perms = unique_perm(str);
    cout << perms.size() << endl;
    for(string curr : perms)
        cout << curr << endl;

    return 0;
}
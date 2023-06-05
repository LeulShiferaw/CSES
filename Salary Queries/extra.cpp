#include <bits/stdc++.h>

using namespace std;

int main()
{
    ifstream Outfile("out");
    ifstream Corrfile("corr_out");

    int temp;
    while(Outfile >> temp)
    {
        int temp2;
        Corrfile >> temp2;

        if(temp != temp2) {
            cout << temp << endl;
        }
    }
    return 0;
}
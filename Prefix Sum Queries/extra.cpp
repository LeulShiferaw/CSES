#include <bits/stdc++.h>

using namespace std;

int main()
{
    ifstream outFile("out");
    ifstream corrFile("corr_out");

    if(!outFile.is_open() || !corrFile.is_open())
    {
        cout << "Error reading file" << endl;
    }
    int temp1; int temp2;
    while(outFile >> temp1) {
        corrFile >> temp2;
        cout << temp1 - temp2 << endl;
    }
    return 0;
}
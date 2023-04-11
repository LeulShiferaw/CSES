#include <iostream>

using namespace std;

//Assume n is even
void display(int n)
{
    if(n == 1) {
        cout << "1 " << endl;
        return;
    }

    if(n > 1 && n <= 3){
        cout << "NO SOLUTION" << endl;
        return;
    }

    if(n == 4) {
        cout << "3 1 4 2 " << endl;
        return;
    }

    int left = 1, right = n/2+1;
    for(int i = 1; i<=n/2; ++i)
    {
        cout << left << " " << right << " ";
        ++left, ++right;
    }
    cout << endl;
}

int main()
{
    int n;
    cin >> n;

    if(n > 1 && n <= 3){
        cout << "NO SOLUTION" << endl;
        return 0;
    }
    if(n%2 == 1)
    {
        cout << n << " ";
        display(n-1);
    }
    else display(n);
}
#include <iostream>

using namespace std;

int main()
{
    long long n;
    cin >> n;

    for(long long i = 1; i<=n; ++i)
    {
        long long res = ((i*i)*((i*i) - 1ll))/2ll -  4ll*(i-2ll)*(i-1ll);
        cout << res << endl;
    }
    return 0;
}
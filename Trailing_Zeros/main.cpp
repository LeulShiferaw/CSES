/*
    Algorithm description

    count the number of 2s in n! even in the factors for example 6 would have one 2 so 6! has 4 2s
    then count the number of 5s in n! even in the factors as well
    then just min(num2, num5) because those ones form a ten leading to trailing zeros

    To count the number of 2s go through all 2^k and see how many multiples they have then add k*(number of multiples)
    becareful not to count multiples of 2^k that have another 2 in them so just consider the odd multiples of 2

    Do the same for 5 but this time subtract out every mutliple of 5^k that has another 5 in it
*/
#include <bits/stdc++.h>

using namespace std;



int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long n;
    cin >> n;


    int k = 0;
    long long curr = 1;
    long long num2 = 0;

    //Count the number of 2s
    while(true)
    {
        ++k;
        curr *= 2;

        if(curr > n)
            break;

        num2 += k*ceil(floor(n/curr)/2.0);
    }

    k = 0;
    curr = 1;  // This would be 5^k
    long long num5 = 0;

    //Count the number of 5s
    while(true)
    {
        ++k;
        curr*=5;
        if(curr > n)
            break;
        long long q = floor(n/curr);
        q -= (q/5); //Subtract out the number of times other fives exist in the multiples
        num5 += q*k;
    }

    cout << min(num2, num5) << endl;
    return 0;
}
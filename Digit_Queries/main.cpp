#include <bits/stdc++.h>

using namespace std;

long long reverse(long long n)
{
    long long res = 0;
    while(n!=0)
    {
        res = res*10 + (n%10);
        n/=10;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;

    while(q--)
    {
        long long n; 
        cin >> n;

        int d = 1;
        long long curr = 1;
        for(d = 1;; ++d)
        {
            n-=d*curr*9LL;

            if(n<0)
            {
                n+=d*curr*9LL;
                break;
            }

            curr*=10LL;
        }
        
        long long x0 = n/d;
        n -= d*x0;
        long long num = (long long)pow(10, d-1) + x0 + (n!=0) - 1;
        cout << n << endl;
        cout << num << endl;
        cout << floor(log10(num)) + 1 << endl;
        if(n == 0)
        {
            cout << num%10 << endl;
        }
        else
        {
            long long temp =1;
            num = reverse(num);
            for(int i = 0; i<n-1; ++i)
                num /= 10;
            cout << num%10 << endl;
        }
    }

    return 0;
}
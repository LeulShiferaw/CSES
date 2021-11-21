#include <bits/stdc++.h>

using namespace std;

void display(const deque<int> &dq)
{
    cout << dq[0];
    for(int i=1; i<dq.size(); ++i)
    {
        cout << " " << dq[i];
    }
    cout << endl;

}

int main()
{
    int n;
    cin >> n;

    deque<int> soln = {2, 4, 1, 3};
    if(n == 1)
        cout << 1 << endl;
    else if(n < 4)
        cout << "NO SOLUTION" << endl;
    else
    {
        bool left = true;
        for(int i = 5; i<=n; ++i)
        {
            if(left)
            {
                left = !left;
                soln.push_front(i);
            }
            else
            {
                left = !left;
                soln.push_back(i);
            }
        }
        display(soln);
    }
    return 0;
}
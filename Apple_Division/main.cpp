#include <bits/stdc++.h>

using namespace std;

void min_diff(long long &min, long long g1, long long g2, int curr_ind, const vector<int> &vec)
{
    if(curr_ind >= vec.size())
    {
        if(abs(g1-g2) < min)
            min = abs(g1-g2);
        return;
    }

    min_diff(min, g1 + vec[curr_ind], g2, curr_ind + 1, vec);
    min_diff(min, g1, g2 + vec[curr_ind], curr_ind + 1, vec);
}

int main()
{
    int n;
    cin >> n;

    vector<int> vec(n);
    for(int i = 0; i<n; ++i)
        cin >> vec[i];

    long long min = LLONG_MAX;
    min_diff(min, 0, 0, 0, vec);

    cout << min << endl;
    return 0;
}

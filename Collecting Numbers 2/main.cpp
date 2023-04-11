#include <bits/stdc++.h>

using namespace std;

/*
    Sort the numbers along with their original position.
    As long as the numbers are in ascending order they will eventually
    be taken out in one round.
    If they are decreasing then add one round for the previous increasing
    sequence. The rounds must start from 1 for the last sequence.
    It can also start from 0 and increment by one at the end.

    This problem is a harder version of Collecting Numbers. In this case:
    We have to get the values of a and b before the swap(na1, nb2) and after
    the swap(na2, nb1). Then the rounds have changed in (na2 + nb1) - (na1, nb2).
    In the rare case that we are swapping two numbers next to each other. We
    have to make sure that we don't count the diff it makes twice on their sharing
    border. That is why we do rounds++ or rounds-- at the end.
*/
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> original(n);
    vector<pair<int, int>> x(n);
    for(int i = 0; i<n; ++i)
    {
        cin >> x[i].first;
        x[i].second = i;

        original[i] = x[i].first;
    }

    sort(x.begin(), x.end());

    int rounds = 1;
    for(int i = 1; i<x.size(); ++i)
    {
        if(x[i-1].second > x[i].second)
            ++rounds;
    }

    for(int i = 0; i<m; ++i)
    {
        int a, b;
        cin >> a >> b;

        int na1 = 0, nb1 = 0, na2 = 0, nb2 = 0;
        int vala = original[a-1], valb = original[b-1];
        if(vala > valb) swap(vala, valb);
        if(vala-1 != 0 && (x[vala-2].second > x[vala-1].second)) ++na1;
        if(vala-1 != n-1 && (x[vala].second < x[vala-1].second)) ++na1;
        if(valb-1 != 0 && (x[valb-2].second > x[valb-1].second)) ++nb2;
        if(valb-1 != n-1 && (x[valb].second < x[valb-1].second)) ++nb2;

        swap(x[original[a-1]-1].second, x[original[b-1]-1].second);
        swap(original[a-1], original[b-1]);

        if(vala-1 != 0 && (x[vala-2].second > x[vala-1].second)) ++na2;
        if(vala-1 != n-1 && (x[vala].second < x[vala-1].second)) ++na2;
        if(valb-1 != 0 && (x[valb-2].second > x[valb-1].second)) ++nb1;
        if(valb-1 != n-1 && (x[valb].second < x[valb-1].second)) ++nb1;

        rounds += (nb1-na1) + (na2-nb2);
        if(valb == vala+1 && x[vala-1].second < x[valb-1].second) rounds++;
        if(valb == vala+1 && x[vala-1].second > x[valb-1].second) rounds--;
        cout << rounds << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
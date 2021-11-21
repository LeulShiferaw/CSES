//For some reason doesn't work for N > 8
#include <bits/stdc++.h>

using namespace std;

#define N 10 

bool col[N];
bool diag1[2*N + 1];
bool diag2[2*N + 1];
bool reserved[N][N];

bool row[N];
bool board[N][N];

void num_ways2(int depth, set<vector<pair<int,int>>> &soln)
{
    cout << depth << endl;
    if(depth >= N)
    {
        vector<pair<int,int>> curr;
        for(int i = 0; i<N; ++i)
        {
            for(int j = 0; j<N; ++j)
            {
                if(board[i][j])
                {
                    curr.push_back(make_pair(i, j));
                }
            }
        }
        soln.insert(curr);
        return;
    }

    for(int i = 0; i<N; ++i)
    {
        if(row[i])
            continue;
        for(int j = 0; j<N; ++j)
        {
            if(col[j])
                continue;
            
            int currx = i-1;
            int curry = j-1;

            bool poss = true;
            while((currx >= 0 && currx < N) && (curry >= 0 && curry < N))
            {
                if(board[currx][curry])
                {
                    poss = false;
                    break;
                }
                --currx;
                --curry;
            }
            if(!poss)
                continue;

            currx = i+1;
            curry = j+1;

            poss = true;
            while((currx >= 0 && currx < N) && (curry >= 0 && curry < N))
            {
                if(board[currx][curry])
                {
                    poss = false;
                    break;
                }
                ++currx;
                ++curry;
            }
            if(!poss)
                continue;

            currx = i+1;
            curry = j-1;

            poss = true;
            while((currx >= 0 && currx < N) && (curry >= 0 && curry < N))
            {
                if(board[currx][curry])
                {
                    poss = false;
                    break;
                }
                ++currx;
                --curry;
            }
            if(!poss)
                continue;

            currx = i-1;
            curry = j+1;

            poss = true;
            while((currx >= 0 && currx < N) && (curry >= 0 && curry < N))
            {
                if(board[currx][curry])
                {
                    poss = false;
                    break;
                }
                --currx;
                ++curry;
            }
            if(!poss)
                continue;

            
            row[i] = true;
            col[j] = true;
            board[i][j] = true;
            
            num_ways2(depth+1, soln);

            row[i] = false;
            col[j] = false;
            board[i][j] = false;
        }
    } 
}

void num_ways(int depth, int &soln)
{
    if(depth >= N)
    {
        ++soln;
        return;
    }

    for(int i = 0; i<N; ++i)
    {
        if(reserved[depth][i])
            continue;
        if(col[i])
            continue;

        int diag_sum = depth + i;
        if(diag2[diag_sum])
            continue;
 
        int diag_diff = depth - i;
        if(diag_diff == 0)
        {
            if(diag1[diag_diff])
                continue;
            diag1[diag_diff] = true;
        }
        else if(diag_diff > 0)
        {
            if(diag1[diag_diff])
                continue;
            diag1[diag_diff] = true;
        }
        else 
        {
            int ind = abs(diag_diff)+7;
            if(diag1[ind])
                continue;
            diag1[ind] = true;
        }

        diag2[diag_sum] = true;
        col[i] = true;

        num_ways(depth+1, soln);

        diag2[diag_sum] = false;
        col[i] = false;
        if(diag_diff == 0)
            diag1[diag_diff] = false;
        else if(diag_diff > 0)
            diag1[diag_diff] = false;
        else 
        {
            int ind = abs(diag_diff)+7;
            diag1[ind] = false;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

/*
    for(int i = 0; i<N; ++i)
    {
        for(int j = 0; j<N; ++j)
        {
            char ch;
            cin >> ch;
            if(ch == '*')
                reserved[i][j] = true;
        }
    }
    */

    int soln = 0;
    num_ways(0, soln);
    cout << soln << endl;
    return 0;
}
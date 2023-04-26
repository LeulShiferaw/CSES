#include <bits/stdc++.h>

using namespace std;

void grid_paths(bool used[][7], int x, int y, int curr, int &soln) 
{
    if(x == 6 && y == 0) {
        if(curr == 48)
            ++soln;
        return;
    } 

    if(x-1 < 0) {
        if(y-1 >= 0 && !used[x][y-1] && y+1 < 7 && !used[x][y+1])
            return;
    }
    
    if(x+1 >= 7) {
        if(y-1 >= 0 && !used[x][y-1] && y+1 < 7 && !used[x][y+1])
            return;
    }

    if(y-1 < 0) {
        if(x-1 >= 0 && !used[x-1][y] && x+1 < 7 && !used[x+1][y])
            return;
    }

    if(y+1 >= 7)
    {
        if(x-1 >= 0 && !used[x-1][y] && x+1 < 7 && !used[x+1][y])
            return;
    }

    //Up
    if(x-1 >= 0 && !used[x-1][y])
    {
        used[x][y] = true;
        grid_paths(used, x-1, y, curr+1, soln);
        used[x][y] = false;
    }

    //Down
    if(x+1 < 7 && !used[x+1][y])
    {
        used[x][y] = true;
        grid_paths(used, x+1, y, curr+1, soln);
        used[x][y] = false;
    }

    //Left
    if(y-1 >= 0 && !used[x][y-1])
    {
        used[x][y] = true;
        grid_paths(used, x, y-1, curr+1, soln);
        used[x][y] = false;
    }

    //Right
    if(y+1 < 7 && !used[x][y+1])
    {
        used[x][y] = true;
        grid_paths(used, x, y+1, curr+1, soln);
        used[x][y] = false;
    }
}

int main()
{
    vector<string> paths;
    bool used[7][7];
    for(int i = 0; i<7; ++i)
        for(int j = 0; j<7; ++j)
            used[i][j] = false;
        
    int res = 0;
    grid_paths(used, 0, 0, 0, res);
    cout << res << endl;
    return 0;
}
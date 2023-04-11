#include <bits/stdc++.h>

using namespace std;

void grid_paths(bool used[][7], int x, int y, string curr, vector<string> &paths)
{
    if(x == 6 && y == 0) {
        if(curr.size() == 48)
        {
            cout << curr << endl;
            paths.push_back(curr);
        }
        return;
    } 

    //Up
    if(x-1 >= 0 && !used[x-1][y])
    {
        used[x][y] = true;
        grid_paths(used, x-1, y, curr+'U', paths);
        used[x][y] = false;
    }
    else if(y-1 >= 0 && !used[x][y-1] && y+1 < 7 && !used[x][y+1])
        return;
    
    
    //Down
    if(x+1 < 7 && !used[x+1][y])
    {
        used[x][y] = true;
        grid_paths(used, x+1, y, curr+'D', paths);
        used[x][y] = false;
    }
    else if(y-1 >= 0 && !used[x][y-1] && y+1 < 7 && !used[x][y+1])
        return;

    //Left
    if(y-1 >= 0 && !used[x][y-1])
    {
        used[x][y] = true;
        grid_paths(used, x, y-1, curr+'L', paths);
        used[x][y] = false;
    }
    else if(x-1 >= 0 && !used[x-1][y] && x+1 < 7 && !used[x+1][y])
        return;

    //Right
    if(y+1 < 7 && !used[x][y+1])
    {
        used[x][y] = true;
        grid_paths(used, x, y+1, curr+'R', paths);
        used[x][y] = false;
    }
    else if(x-1 >= 0 && !used[x-1][y] && x+1 < 7 && !used[x+1][y])
        return;
    return;
}

int main()
{
    vector<string> paths;
    bool used[7][7];
    for(int i = 0; i<7; ++i)
        for(int j = 0; j<7; ++j)
            used[i][j] = false;
        
    string curr = "";
    grid_paths(used, 0, 0, curr, paths);
    cout << paths.size() << endl;
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

//Do recursion to find answer.
//With some optimizations. If it touches a wall and can go
//both right and left then end it there
//A wall can be both a used square or then end of the grid
//But if it is a used square make sure the last move matches it
//like if it is a wall at the top then last move should be up
//otherwise it will match other cases
void grid_paths(bool used[][7], int x, int y, int curr, int &soln, const string &input) 
{
    if(x == 6 && y == 0) {
        if(curr == 48)
            ++soln;
        return;
    } 

    //End of grid
    if((x-1 < 0)) {
        if(((y-1) >= 0) && (!used[x][y-1]) && ((y+1) < 7) && (!used[x][y+1]))
            return;
    }
    if(x+1 >= 7) {
        if((y-1 >= 0) && (!used[x][y-1]) && (y+1 < 7) && !used[x][y+1])
            return;
    }
    if(y-1 < 0) {
        if((x-1 >= 0) && !used[x-1][y] && (x+1 < 7) && !used[x+1][y])
            return;
    }
    if(y+1 >= 7)
    {
        if((x-1 >= 0) && !used[x-1][y] && (x+1 < 7) && !used[x+1][y])
            return;
    }

    //Up
    if((x-1 >= 0) && !used[x-1][y] && (input[curr] == '?' || input[curr] == 'U'))
    {
        //A wall
        bool ok = true;
        if((x-2 >= 0) && used[x-2][y]) {
            if(((y-1) >= 0) && (!used[x-1][y-1]) && ((y+1) < 7) && (!used[x-1][y+1]))
                ok = false;
        }
        if(ok)
        {
            used[x][y] = true;
            grid_paths(used, x-1, y, curr+1, soln, input);
            used[x][y] = false;
        }
    }

    //Down
    if((x+1 < 7) && !used[x+1][y] && (input[curr] == '?' || input[curr] == 'D'))
    {
        //A wall
        bool ok = true;
        if((x+2 >= 0) && used[x+2][y]) {
            if(((y-1) >= 0) && (!used[x+1][y-1]) && ((y+1) < 7) && (!used[x+1][y+1]))
                ok = false;
        }
        if(ok) {
            used[x][y] = true;
            grid_paths(used, x+1, y, curr+1, soln, input);
            used[x][y] = false;
        }
    }

    //Left
    if((y-1 >= 0) && !used[x][y-1] && (input[curr] == '?' || input[curr] == 'L'))
    {
        //A wall
        bool ok = true;
        if((y-2 >= 0) && used[x][y-2]) {
            if(((x-1) >= 0) && (!used[x-1][y-1]) && ((x+1) < 7) && (!used[x+1][y-1]))
                ok = false;
        }
        if(ok) {
            used[x][y] = true;
            grid_paths(used, x, y-1, curr+1, soln, input);
            used[x][y] = false;
        }
    }

    //Right
    if((y+1 < 7) && !used[x][y+1] && (input[curr] == '?' || input[curr] == 'R'))
    {
        //A wall
        bool ok = true;
        if((y+2 >= 0) && used[x][y+2]) {
            if(((x-1) >= 0) && (!used[x-1][y+1]) && ((x+1) < 7) && (!used[x+1][y+1]))
                ok = false;
        }
        if(ok) {
            used[x][y] = true;
            grid_paths(used, x, y+1, curr+1, soln, input);
            used[x][y] = false;
        }
    }
}

int main()
{
    string grid;
    cin >> grid;
    vector<string> paths;
    bool used[7][7];
    for(int i = 0; i<7; ++i)
        for(int j = 0; j<7; ++j)
            used[i][j] = false;
        
    int res = 0;
    grid_paths(used, 0, 0, 0, res, grid);
    std::cout << res << endl;
    return 0;
}
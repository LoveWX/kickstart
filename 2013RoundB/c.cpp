#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n;
bool linked;

inline bool IsValid(int x, int y)
{
    return 0 <= x && x < n && 0 <= y && y < n;
}

void dfsRed(vector<string> &grid, vector<vector<bool>> &visited, int x, int y)
{
    if (linked) return;
    if (!IsValid(x, y) || visited[x][y] || grid[x][y] != 'R') return;
    if (x == n - 1)
    {
        linked = true;
        return;
    }
    visited[x][y] = true;
    dfsRed(grid, visited, x - 1, y);
    dfsRed(grid, visited, x - 1, y + 1);
    dfsRed(grid, visited, x, y - 1);
    dfsRed(grid, visited, x, y + 1);
    dfsRed(grid, visited, x + 1, y - 1);
    dfsRed(grid, visited, x + 1, y);
}

bool LinkedRed(vector<string> &grid)
{
    linked = false;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    for (int j = 0; j < n; ++j)
    {
        dfsRed(grid, visited, 0, j);
    }
    return linked;
}

void dfsBlue(vector<string> &grid, vector<vector<bool>> &visited, int x, int y)
{
    if (linked) return;
    if (!IsValid(x, y) || visited[x][y] || grid[x][y] != 'B') return;
    if (y == n - 1)
    {
        linked = true;
        return;
    }
    visited[x][y] = true;
    dfsBlue(grid, visited, x - 1, y);
    dfsBlue(grid, visited, x - 1, y + 1);
    dfsBlue(grid, visited, x, y - 1);
    dfsBlue(grid, visited, x, y + 1);
    dfsBlue(grid, visited, x + 1, y - 1);
    dfsBlue(grid, visited, x + 1, y);
}

bool LinkedBlue(vector<string> &grid)
{
    linked = false;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i)
    {
        dfsBlue(grid, visited, i, 0);
    }
    return linked;
}

int main()
{
    int ncase;
    cin >> ncase;
    for (int icase = 1; icase <= ncase; ++icase)
    {
        cin >> n;
        vector<string> grid(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> grid[i];
        }
        int r = 0, b = 0,status=-1;
        for (string &s : grid)
        {
            for (char c : s)
            {
                if (c == 'R') ++r;
                else if (c == 'B') ++b;
            }
        }
        do
        {
            if (abs(r - b) > 1)
            {
                break;
            }
            bool cutFound = false;
            if (LinkedRed(grid))
            {
                if (r < b) break;
                for (int i = 0; i < n; ++i)
                {
                    for (int j = 0; j < n; ++j)
                    {
                        if (grid[i][j] == 'R')
                        {
                            grid[i][j] = '.';
                            bool isLinked = LinkedRed(grid);
                            grid[i][j] = 'R';
                            if (!isLinked)
                            {
                                cutFound = true;
                                i = n;
                                break;
                            }
                        }
                    }
                }
                if (cutFound)
                {
                    status = 1;
                }
                break;
            }
            cutFound = false;
            if (LinkedBlue(grid))
            {
                if (b < r) break;
                for (int i = 0; i < n; ++i)
                {
                    for (int j = 0; j < n; ++j)
                    {
                        if (grid[i][j] == 'B')
                        {
                            grid[i][j] = '.';
                            bool isLinked = LinkedBlue(grid);
                            grid[i][j] = 'B';
                            if (!isLinked)
                            {
                                cutFound = true;
                                i = n;
                                break;
                            }
                        }
                    }
                }
                if (cutFound)
                {
                    status = 2;
                }
                break;
            }
            status = 0;
        } while (0);
        cout << "Case #" << icase << ": ";
        if (status == -1)
        {
            cout << "Impossible" << endl;
        }
        else if (status == 1)
        {
            cout << "Red wins" << endl;
        }
        else if (status == 2)
        {
            cout << "Blue wins" << endl;
        }
        else
        {
            cout << "Nobody wins" << endl;
        }
    }
    return 0;
}

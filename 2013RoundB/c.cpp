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

int findr(vector<int> &parent, int x)
{
    int r = x, i = x, j;
    for (; r != parent[r]; r = parent[r]);
    while (i != r)
    {
        j = parent[i];
        parent[i] = r;
        i = j;
    }
    return r;
}

void unionr(vector<int> &parent, vector<int> &rank, int x, int y)
{
    int rx = findr(parent, x), ry = findr(parent, y);
    if (rank[rx] < rank[ry])
    {
        parent[rx] = ry;
    }
    else if (rank[rx] > rank[ry])
    {
        parent[ry] = rx;
    }
    else
    {
        parent[ry] = rx;
        rank[rx] += 1;
    }
}

bool IsLinked(vector<string> &grid, char ch)
{
    linked = false;
    int nn = n*n;
    vector<int> parent(nn + 2), rank(nn + 2, 0);
    for (int i = 0; i < nn + 2; ++i)
    {
        parent[i] = i;
    }
    if (ch == 'R')
    {
        for (int j = 0; j < n; ++j)
        {
            if (grid[0][j] == 'R')
            {
                unionr(parent, rank, nn, j);
            }
            if (grid[n - 1][j] == 'R')
            {
                unionr(parent, rank, nn + 1, nn - n + j);
            }
        }
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            if (grid[i][0] == 'B')
            {
                unionr(parent, rank, nn, i*n);
            }
            if (grid[i][n - 1] == 'B')
            {
                unionr(parent, rank, nn + 1, i*n + n - 1);
            }
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            if (grid[i][j - 1] == ch && grid[i][j] == ch)
            {
                unionr(parent, rank, i*n + j - 1, i*n + j);
            }
        }
    }
    for (int j = 0; j < n; ++j)
    {
        for (int i = 1; i < n; ++i)
        {
            if (grid[i - 1][j] == ch && grid[i][j] == ch)
            {
                unionr(parent, rank, (i - 1)*n + j, i*n + j);
            }
        }
    }
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            if (grid[i + 1][j - 1] == ch && grid[i][j] == ch)
            {
                unionr(parent, rank, (i + 1)*n + j - 1, i*n + j);
            }
        }
    }
    return findr(parent, nn) == findr(parent, nn + 1);
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
            //if (LinkedRed)
            if (IsLinked(grid, 'R'))
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
            //if (LinkedBlue)
            if (IsLinked(grid, 'B'))
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

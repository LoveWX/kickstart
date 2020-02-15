#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int row, col;
int dx[] = { 1,0,-1,0 };
int dy[] = { 0,1,0,-1 };

inline bool InBoard(vector<vector<int>> &mat, int x, int y)
{
	return 0 <= x && x < row && 0 <= y && y < col && mat[x][y] != -1;
}

bool cmp(vector<int> &a, vector<int> &b)
{
	return a[2] > b[2];
}

int main()
{
	int ncase;
	cin >> ncase;
	int sx, sy, ex, ey, anspower;
	for (int icase = 1; icase <= ncase; ++icase)
	{
		cin >> row >> col;
		vector<vector<int>> mat(row, vector<int>(col));
		cin >> sx >> sy >> ex >> ey;
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				cin >> mat[i][j];
			}
		}
		vector<vector<bool>> visited(row, vector<bool>(col, false));
		vector<vector<int>> curr(1, { sx,sy,0 });
		while (!curr.empty())
		{
			sort(curr.begin(), curr.end(), cmp);
			vector<vector<int>> next;
			for (vector<int> &vi : curr)
			{
				int xx = vi[0], yy = vi[1];
				if (visited[xx][yy]) continue;
				visited[xx][yy] = true;
				int pp = vi[2] + mat[xx][yy];
				if (xx == ex && yy == ey)
				{
					anspower = pp;
					break;
				}
				for (int d = 0; d < 4; ++d)
				{
					int nx = xx + dx[d], ny = yy + dy[d];
					if (InBoard(mat, nx, ny) && !visited[nx][ny])
					{
						next.push_back({ nx,ny,pp });
					}
				}
			}
			if (visited[ex][ey]) break;
			curr = move(next);
		}
		cout << "Case #" << icase << ": ";
		if (visited[ex][ey])
		{
			cout << anspower << endl;
		}
		else
		{
			cout << "Mission Impossible." << endl;
		}
	}

	return 0;
}

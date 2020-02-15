#include <iostream>
#include <string>
#include <vector>
using namespace std;

int turnleft[] = { 3,0,1,2 };
int turnright[] = { 1,2,3,0 };
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };
int hx[] = { -1,0,1,0 };
int hy[] = { 0,1,0,-1 };
char step[] = "ESWN";

bool trytomove(vector<string> &grid, int x, int y, int ex, int ey, int d, string &ans)
{
	ans.clear();
	int stepleft = 10000, nx, ny;
	while (stepleft > 0)
	{
		nx = x + dx[d];
		ny = y + dy[d];
		if (grid[nx][ny] == '#')
		{
			d = turnright[d];
			continue;
		}
		ans.push_back(step[d]);
		--stepleft;
		x = nx;
		y = ny;
		if (x == ex && y == ey) break;
		nx = x + hx[d];
		ny = y + hy[d];
		if (grid[nx][ny] == '.')
		{
			d = turnleft[d];
			ans.push_back(step[d]);
			--stepleft;
			x = nx;
			y = ny;
			if (x == ex && y == ey) break;
		}
	}
	return (x == ex && y == ey && stepleft >= 0);
}

int main()
{
	int ncase, n;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
		cin >> n;
		string ts;
		getline(cin, ts);
		vector<string> grid(n + 2);
		grid[0] = string(n + 2, '#');
		grid.back() = grid[0];
		for (int i = 1; i <= n; ++i)
		{
			getline(cin, ts);
			grid[i] = string("#") + ts + string("#");
		}
		int sx, sy, ex, ey, d;
		cin >> sx >> sy >> ex >> ey;
		bool found = false;
		if (!(grid[sx + dx[0]][sy + dy[0]] == '#' &&
			grid[sx + dx[1]][sy + dy[1]] == '#' &&
			grid[sx + dx[2]][sy + dy[2]] == '#' &&
			grid[sx + dx[3]][sy + dy[3]] == '#'))
		{
			if (sx == 1 && sy == 1)
			{
				d = grid[sx + dx[0]][sy + dy[0]] == '#' ? 1 : 0;
			}
			else if (sx == 1)
			{
				d = grid[sx + dx[1]][sy + dy[1]] == '#' ? 2 : 1;
			}
			else if (sy == 1)
			{
				d = grid[sx + dx[3]][sy + dy[3]] == '#' ? 0 : 3;
			}
			else
			{
				d = grid[sx + dx[2]][sy + dy[2]] == '#' ? 3 : 2;
			}
			found = trytomove(grid, sx, sy, ex, ey, d, ts);
		}
		cout << "Case #" << icase << ": ";
		if (!found)
		{
			cout << "Edison ran out of energy." << endl;
		}
		else
		{
			cout << ts.length() << endl << ts << endl;
		}
	}
	return 0;
}

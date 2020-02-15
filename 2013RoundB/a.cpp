#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool IsValid(vector<int> &vi)
{
	sort(vi.begin(), vi.end());
	for (int i = 0; i < vi.size(); ++i)
	{
		if (vi[i] != i + 1)
		{
			return false;
		}
	}
	return true;
}

bool IsValid(vector<vector<int>> &mat, int n, int nn)
{
	vector<int> vi(nn);
	for (int j = 0; j < nn; ++j)
	{
		for (int i = 0; i < nn; ++i)
		{
			vi[i] = mat[i][j];
		}
		if (!IsValid(vi))
		{
			return false;
		}
	}
	int k;
	for (int ii = 0; ii < nn; ii += n)
	{
		for (int jj = 0; jj < nn; jj += n)
		{
			k = 0;
			for (int i = ii; i < ii + n; ++i)
			{
				for (int j = jj; j < jj + n; ++j)
				{
					vi[k++] = mat[i][j];
				}
			}
			if (!IsValid(vi))
			{
				return false;
			}
		}
	}
	for (int i = 0; i < nn; ++i)
	{
		if (!IsValid(mat[i]))
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int ncase, n, nn;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
		cin >> n;
		nn = n*n;
		vector<vector<int>> mat(nn, vector<int>(nn));
		for (int i = 0; i < nn; ++i)
		{
			for (int j = 0; j < nn; ++j)
			{
				cin >> mat[i][j];
			}
		}
		cout << "Case #" << icase << ": " << (IsValid(mat, n, nn) ? "Yes" : "No") << endl;
	}
	return 0;
}

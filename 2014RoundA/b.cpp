#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n;

void merge(vector<int> &vi, vector<int> &ans)
{
    int last = -1;
    for (int i : vi)
    {
        if (i != 0)
        {
            if (i == last)
            {
                ans.back() += i;
                last = -1;
            }
            else
            {
                ans.push_back(i);
                last = i;
            }
        }
    }
    while (ans.size() < n)
    {
        ans.push_back(0);
    }
}

void mergeup(vector<vector<int>> &mat)
{
    for (int j = 0; j < n; ++j)
    {
        vector<int> vi(n), vm;
        for (int i = 0; i < n; ++i)
        {
            vi[i] = mat[i][j];
        }
        merge(vi, vm);
        for (int i = 0; i < n; ++i)
        {
            mat[i][j] = vm[i];
        }
    }
}

void mergedown(vector<vector<int>> &mat)
{
    for (int j = 0; j < n; ++j)
    {
        vector<int> vi(n), vm;
        for (int i = 0, k = n - 1; i < n; ++i, --k)
        {
            vi[i] = mat[k][j];
        }
        merge(vi, vm);
        for (int i = 0, k = n - 1; i < n; ++i, --k)
        {
            mat[k][j] = vm[i];
        }
    }
}

void mergeleft(vector<vector<int>> &mat)
{
    for (int i = 0; i < n; ++i)
    {
        vector<int> vm;
        merge(mat[i], vm);
        for (int j = 0; j < n; ++j)
        {
            mat[i][j] = vm[j];
        }
    }
}

void mergeright(vector<vector<int>> &mat)
{
    for (int i = 0; i < n; ++i)
    {
        vector<int> vi(n), vm;
        for (int j = 0, k = n - 1; j < n; ++j, --k)
        {
            vi[j] = mat[i][k];
        }
        merge(vi, vm);
        for (int j = 0, k = n - 1; j < n; ++j, --k)
        {
            mat[i][k] = vm[j];
        }
    }
}

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        string dir;
        cin >> n >> dir;
        vector<vector<int>> mat(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cin >> mat[i][j];
            }
        }
        if (dir == "left")
        {
            mergeleft(mat);
        }
        else if (dir == "right")
        {
            mergeright(mat);
        }
        else if (dir == "up")
        {
            mergeup(mat);
        }
        else
        {
            mergedown(mat);
        }
        cout << "Case #" << icase << ":" << endl;
        for (vector<int> &vi : mat)
        {
            cout << vi[0];
            for (int i = 1; i < n; ++i)
            {
                cout << ' ' << vi[i];
            }
            cout << endl;
        }
	}
	return 0;
}

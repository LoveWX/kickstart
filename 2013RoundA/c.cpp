#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int ncase,n,t;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
		cin >> n;
		vector<int> oddpos, oddval, evenpos, evenval;
		for (int i = 0; i < n; ++i)
		{
			cin >> t;
			if (t % 2 == 0)
			{
				evenpos.push_back(i);
				evenval.push_back(t);
			}
			else
			{
				oddpos.push_back(i);
				oddval.push_back(t);
			}
		}
	}
	return 0;
}

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	int ncase, n;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
		cin >> n;
		vector<string> vs(n);
		getline(cin, vs[0]);
		for (int i = 0; i < n; ++i)
		{
			getline(cin, vs[i]);
		}
		int ans = 0, last = 0;
		for (int i = 1; i < n; ++i)
		{
			if (vs[i] < vs[last])
			{
				++ans;
			}
			else
			{
				last = i;
			}
		}
		cout << "Case #" << icase << ": " << ans << endl;
	}
	return 0;
}

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        int len;
        string A, B;
        cin >> len >> A >> B;
        map<int, set<string>> m;
        for (int i = 0; i < len; ++i)
        {
            for (int j = i; j < len; ++j)
            {
                string s = B.substr(i, j - i + 1);
                sort(s.begin(), s.end());
                m[j - i + 1].insert(move(s));
            }
        }
        int ans = 0;
        for (int i = 0; i < len; ++i)
        {
            for (int j = i; j < len; ++j)
            {
                string s = A.substr(i, j - i + 1);
                sort(s.begin(), s.end());
                ans += m[j - i + 1].count(s);
            }
        }
        cout << "Case #" << icase << ": " << ans << endl;
	}
	return 0;
}

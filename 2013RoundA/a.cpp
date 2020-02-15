#include <iostream>
#include <string>
#include <vector>
using namespace std;

string snum[] = { "zero ","one ","three ","four ","five ","six ","seven ","eight ","nine " };
string smulti[] = { "","","double ","triple ","quadruple ","quintuple ","sextuple ","septuple ","octuple ","nonuple ","decuple " };

string readnum(string &s, int start, int end)
{
	string ans;
	for (int i = start; i <= end;)
	{
		int j = i + 1;
		for (; j <= end && s[i] == s[j]; ++j) {}
		int count = j - i;
		string &ts = snum[s[i] - '0'];
		if (count <= 10)
		{
			ans += smulti[count];
			ans += ts;
		}
		else
		{
			while (count--)
			{
				ans += ts;
			}
		}
		i = j;
	}
	return move(ans);
}

int main()
{
	int ncase;
	cin >> ncase;
	string sa, sb;
	for (int icase = 1; icase <= ncase; ++icase)
	{
		cin >> sa >> sb;
		sb.push_back('-');
		vector<int> vi;
		int last = 0;
		for (int i = 0; i < sb.length(); ++i)
		{
			if (sb[i] == '-')
			{
				vi.push_back(stoi(sb.substr(last, i - last)));
				last = i + 1;
			}
		}
		last = 0;
		string ans;
		for (int k : vi)
		{
			ans += readnum(sa, last, last + k - 1);
			last += k;
		}
		ans.pop_back();
		cout << "Case #" << icase << ": " << ans << endl;
	}
	return 0;
}

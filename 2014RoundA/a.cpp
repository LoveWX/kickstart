#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

int n;
string num[] = { "1111110", "0110000", "1101101", "1111001", "0110011", "1011011", "1011111", "1110000", "1111111", "1111011" };

string check(vector<string> &states, int curr)
{
    string led(7, '2');
    for (string &state : states)
    {
        string &snum = num[curr];
        curr = (curr - 1 + 10) % 10;
        for (int j = 0; j < 7; ++j)
        {
            if (snum[j] == '0')
            {
                if (state[j] == '1') return "a";
            }
            else
            {
                if (led[j] == '2')
                {
                    led[j] = state[j];
                }
                else if (led[j] != state[j])
                {
                    return "a";
                }
            }
        }
    }
    string ans(7, '2');
    string &snum = num[curr];
    for (int i = 0; i < 7; ++i)
    {
        if (snum[i] == '0')
        {
            ans[i] = '0';
        }
        else
        {
            if (led[i] == '2') return "b";
            ans[i] = led[i];
        }
    }
    return move(ans);
}

string checkall(vector<string> &states)
{
    if (n >= 10)
    {
        return states[n % 10];
    }
    set<string> setans;
    for (int i = 0; i <= 9; ++i)
    {
        string ts = check(states, i);
        if (ts == "b")
        {
            return "ERROR!";
        }
        else if (ts != "a")
        {
            setans.insert(ts);
        }
    }
    return setans.size() == 1 ? *setans.begin() : "ERROR!";
}

int main()
{
    int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        cin >> n;
        vector<string> states(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> states[i];
        }
        cout << "Case #" << icase << ": " << checkall(states) << endl;
	}
	return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<unsigned long long> starti;

void f1(unsigned long long n, unsigned long long &p, unsigned long long &q)
{
	vector<int> oper;
	int i = upper_bound(starti.begin(), starti.end(), n) - starti.begin() - 1;
	for (; i > 0; --i)
	{
		oper.push_back((n - starti[i]) % 2);
		n >>= 1;
	}
	p = 1;
	q = 1;
	for (i = oper.size() - 1; i >= 0; --i)
	{
		if (oper[i] == 0)
		{
			q = p + q;
		}
		else
		{
			p = p + q;
		}
	}
}

void f2(unsigned long long &n, unsigned long long p, unsigned long long q)
{
	vector<int> oper;
	while (p > 1 || q > 1)
	{
		if (p < q)
		{
			oper.push_back(0);
			q -= p;
		}
		else
		{
			oper.push_back(1);
			p -= q;
		}
	}
	n = 1;
	for (int i = oper.size() - 1; i >= 0; --i)
	{
		n = n * 2 + oper[i];
	}
}

int main()
{
	starti.assign(64, 1ULL);
	for (int i = 1; i < 64; ++i)
	{
		starti[i] = starti[i - 1] << 1;
	}
	int ncase,type;
	cin >> ncase;
	unsigned long long n, p, q;
	for (int icase = 1; icase <= ncase; ++icase)
	{
		cout << "Case #" << icase << ": ";
		cin >> type;
		if (type == 1)
		{
			cin >> n;
			f1(n, p, q);
			cout << p << ' ' << q << endl;
		}
		else
		{
			cin >> p >> q;
			f2(n, p, q);
			cout << n << endl;
		}
	}
	return 0;
}

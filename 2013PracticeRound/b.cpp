#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
	double g = 9.8, pi = 3.1415926535897932384626433832795;
	int ncase, V, D;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
		cin >> V >> D;
		double thata = g*D / V / V;
		if (thata > 1.0)
		{
			thata = 1.0;
		}
		thata = asin(thata) / 2 * 180 / pi;
		cout << "Case #" << icase << ": " << fixed << setprecision(7) << thata << endl;
	}
	return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        int N, t;
        cin >> N;
        cout << "Case #" << icase << ":";
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 0; i < N; ++i)
        {
            cin >> t;
            pq.push(t);
            while (pq.size() > pq.top())
            {
                pq.pop();
            }
            cout << ' ' << pq.size();
        }
        cout << endl;
	}
	return 0;
}

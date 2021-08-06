#include <iostream>
#include <vector>
using namespace std;

const int SIZE = 100000;
int N, Q, P;
long long A[SIZE + 1];
//long long A;

int prefixSum(vector<int> &bit, int idx)
{
    int sum = 0;
    while (idx != 0)
    {
        sum += bit[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

void update(vector<int> &bit, int idx, int diff)
{
    while (idx <= N)
    {
        bit[idx] += diff;
        idx += (idx & -idx);
    }
}

int rangeSum(vector<int> &bit, int idx1, int idx2)
{
    return prefixSum(bit, idx2) - prefixSum(bit, idx1 - 1);
}

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        cin >> N >> Q >> P;
        vector<int> bit0(N + 1, 0);
        vector<int> bit1(N + 1, 0);
        vector<int> bit2(N + 1, 0);
        for (int i = 1; i <= N; ++i)
        {
            cin >> A[i];
            if (A[i] % P == 0)
            {
                int a = 0;
                for (long long t = A[i]; t % P == 0; t /= P, ++a);
                update(bit0, i, a);
            }
            else
            {
                int a = 0;
                for (long long t = A[i] - A[i] % P; t % P == 0; t /= P, ++a);
                update(bit1, i, a);
                update(bit2, i, 1);
            }
        }
        cout << "Case #" << icase << ':';
        for (; Q > 0; --Q)
        {
            int type;
            cin >> type;
            if (type == 1)
            {
                int pos, a = 0;
                long long val;
                cin >> pos >> val;
                if (A[pos] % P == 0)
                {
                    //for (long long t = val; t % P == 0; t /= P, ++a);
                    update(bit0, pos, -rangeSum(bit0, pos, pos));
                }
                else
                {
                    update(bit1, pos, -rangeSum(bit1, pos, pos));
                    update(bit2, pos, -1);
                }
                if (val % P == 0)
                {
                    for (long long t = val; t % P == 0; t /= P, ++a);
                    update(bit0, pos, a);
                }
                else
                {
                    for (long long t = val; t % P == 0; t /= P, ++a);
                    update(bit1, pos, a);
                    update(bit2, pos, 1);
                }
            }
            else
            {
                long long S;
                int L, R;
                cin >> S >> L >> R;
                int a = 1;
                for (long long t = S; S % P == 0; S /= P, ++a);
                cout << ' ' << S * rangeSum(bit0, L, R) + a * rangeSum(bit2, L, R) + rangeSum(bit1, L, R);
            }
        }
        cout << endl;
	}
	return 0;
}

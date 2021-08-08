#include <iostream>
#include <vector>
using namespace std;

const int SIZE = 500000;
long long A[SIZE + 1];
int N, Q, P;

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

int V(long long val)
{
    int a = 0;
    for (; val >= P && val % P == 0; val /= P, ++a);
    return a;
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
        vector<int> bit3(N + 1, 0);
        for (int i = 1; i <= N; ++i)
        {
            cin >> A[i];
            if (A[i] % P == 0)
            {
                update(bit0, i, V(A[i]));
            }
            else if (A[i] > P)
            {
                update(bit1, i, V(A[i] - A[i] % P));
                if (P == 2 && A[i] % 4 == 3) update(bit2, i, V(A[i] + A[i] % P) - 1);//P==2 && (Ai-(Ai%P))%4!=0
                update(bit3, i, 1);
            }
        }
        cout << "Case #" << icase << ':';
        for (; Q > 0; --Q)
        {
            int type;
            cin >> type;
            if (type == 1)
            {
                int pos;
                long long val;
                cin >> pos >> val;
                if (A[pos] % P == 0)
                {
                    update(bit0, pos, -V(A[pos]));
                }
                else if (A[pos] > P)
                {
                    update(bit1, pos, -V(A[pos] - A[pos] % P));
                    if (P == 2 && A[pos] % 4 == 3) update(bit2, pos, 1 - V(A[pos] + A[pos] % P));
                    update(bit3, pos, -1);
                }
                if (val % P == 0)
                {
                    update(bit0, pos, V(val));
                }
                else if (val > P)
                {
                    update(bit1, pos, V(val - val % P));
                    if (P == 2 && val % 4 == 3) update(bit2, pos, V(val + val % P) - 1);
                    update(bit3, pos, 1);
                }
                A[pos] = val;
            }
            else
            {
                long long S;
                int L, R;
                cin >> S >> L >> R;
                long long ans = S * rangeSum(bit0, L, R) + rangeSum(bit1, L, R) + V(S) * rangeSum(bit3, L, R);
                if (P == 2 && S % 2 == 0)
                {
                    ans += rangeSum(bit2, L, R);
                }
                cout << ' ' << ans;
            }
        }
        cout << endl;
    }
    return 0;
}

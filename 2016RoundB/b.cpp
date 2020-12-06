#include <iostream>
#include <cstring>
using namespace std;

const long long mod = 1000000007;
long long countA[100000];
long long countB[100000];

int Remainder(long long x,int a,int k)
{
    long long ans = 1LL;
    while (a != 0)
    {
        if ((a & 1) != 0)
        {
            ans = ans*x%k;
        }
        a >>= 1;
        x = x*x%k;
    }
    return ans % k;
}

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        int A, B, K;
        long long N;
        cin >> A >> B >> N >> K;
        memset(countA, 0, K * sizeof(long long));
        memset(countB, 0, K * sizeof(long long));
        long long t1 = N / K, t2 = N % K;
        long long count0 = 0;
        for (int i = 1; i <= K; ++i)
        {
            long long t = t1 + (t2 >= i ? 1 : 0);
            int ra = Remainder(i, A, K), rb = Remainder(i, B, K);
            countA[ra] += t;
            countB[rb] += t;
            if ((ra + rb) % K == 0)
            {
                count0 += t;
            }
        }
        for (int i = 0; i < K; ++i)
        {
            countA[i] %= mod;
            countB[i] %= mod;
        }
        long long ans = countA[0] * countB[0] % mod;
        for (int i = 1; i < K; ++i)
        {
            ans += countA[i] * countB[K - i] % mod;
        }
        ans = (ans - count0 % mod + mod) % mod;
        cout << "Case #" << icase << ": " << ans << endl;
	}
	return 0;
}

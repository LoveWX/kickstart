#include <iostream>
#include <vector>
#include <map>
using namespace std;

int N, G, M;

int main()
{
    int ncase;
    cin >> ncase;
    for (int icase = 1; icase <= ncase; ++icase)
    {
        cin >> N >> G >> M;
        map<int, int> mc, ma;
        vector<map<int, int>::iterator> vpit(G);
        for (int i = 0; i<G; ++i)
        {
            int p;
            char c;
            cin >> p >> c;
            p -= 1;
            map<int, int> &m = (c == 'c' ? mc : ma);
            m[p] = 0;
            vpit[i] = m.find(p);
        }
        for (int i = 0; i<N; ++i)
        {
            int cfirstmeet, afirstmeet, clastmeet, alastmeet;
            auto itc = ma.upper_bound(i);
            if (itc == ma.end())
            {
                cfirstmeet = N - i + ma.begin()->first;
            }
            else
            {
                cfirstmeet = itc->first - i;
            }
            int clastpos = (i + M) % N;
            itc = ma.upper_bound(clastpos);
            if (itc == ma.begin())
            {
                itc = prev(ma.end());
                clastmeet = clastpos + N - itc->first;
            }
            else
            {
                itc = prev(itc);
                clastmeet = clastpos - itc->first;
            }
            auto ita = mc.lower_bound(i);
            if (ita == mc.begin())
            {
                afirstmeet = i + N - prev(mc.end())->first;
            }
            else
            {
                afirstmeet = i - prev(ita)->first;
            }
            int alastpos = ((i - M) % N + N) % N;
            ita = mc.upper_bound(alastpos);
            if (ita == mc.end())
            {
                ita = mc.begin();
                alastmeet = alastpos + N - ita->first;
            }
            else
            {
                ita = prev(ita);
                alastmeet = alastpos - ita->first;
            }
            if (cfirstmeet >= M && afirstmeet >= M)
            {
                if (clastmeet < alastmeet)
                {
                    itc->second += 1;
                }
                else if (clastmeet > alastmeet)
                {
                    ita->second += 1;
                }
                else
                {
                    itc->second += 1;
                    ita->second += 1;
                }
            }
            else if (cfirstmeet >= M)
            {
                itc->second += 1;
            }
            else if (afirstmeet >= M)
            {
                ita->second += 1;
            }
        }
        cout << "Case #" << icase << ":";
        for (int i = 0; i<G; ++i)
        {
            cout << ' ' << vpit[i]->second;
        }
        cout << endl;
    }
    return 0;
}

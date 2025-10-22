/**
 * Author: Nando
 * License: CC0
 * Source: Codeforces
 * Description: DP transisi = mx + c
 * Time: O(N log N)
 * Status: -
 */
pii tpot(pii satu, pii dua)
{
    pii jwb;
    jwb.first = dua.second - satu.second;
    jwb.second = satu.first - dua.first;
    return jwb;
}
bool cmp(pii a, pii b)
{
    if (a.fi / a.se == b.fi / b.se)
    {
        a.fi %= a.se;
        b.fi %= b.se;
        return a.fi * b.se <= b.fi * a.se;
    }
    return a.fi / a.se <= b.fi / b.se;
}
line.push_back({1, -pref[0]}); // cari maksimum , gradien non decreasing //m and c
// cari minimum gradien non increasing
for (LL i = 2; i <= n; i++)
{
    LL x = a[i];
    LL ki = 1, ka = (LL)line.size() - 1, add = -1e18;
    while (ki <= ka)
    {
        LL mid = (ki + ka) / 2;
        LL l = line[mid - 1].first * x + line[mid - 1].second;
        LL r = line[mid].first * x + line[mid].second;
        add = max(add, max(l, r));
        if (l > r)
            ka = mid - 1;
        else
            ki = mid + 1;
        /*
        Minimum
        add=min(add,min(l,r))
        if(l>r)ki=mid+1;
        else ka=mid-1;
        */
    }
    if (line.size() == 1)
        add = line[0].first * x + line[0].second;
    ans = max(ans, ret + add - a[i] * i + pref[i - 1]); // tambahin constant
    pii now = {i, -pref[i - 1]};
    LL skg = line.size() - 1, prev = line.size() - 2;
    while (skg > 0 && cmp(tpot(now, line[skg]), tpot(now, line[prev])))
    {
        // hapus yang gamasuk hull
        line.pop_back();
        skg--;
        prev--;
    }
    line.push_back(now);
}
/**
 * Author: Nando
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: Slope Trick
 * Time: O(N \log N)
 */

// min step non-decreasing
cin >> n;
for (LL i = 1; i <= n; i++)
{
    cin >> a;
    a -= i;
    PQ.push(a);
    PQ.push(a);
    ans += PQ.top() - a;
    PQ.pop();
}
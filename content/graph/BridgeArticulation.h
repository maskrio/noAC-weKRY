/**
 * Author: Nando
 * Date: 2015-02-06
 * License: CC0
 * Description: Finding bridges and articulation points
 * Time: construction $O(V + E)$
 * Status: -
 */

int time;

void dfs(int u, int parent)
{
    disc[u] = low[u] = time++;
    for (int v : adj[u])
    {
        if (disc[v] == -1)
        {
            ++child[u];
            dfs(v, u);
            if (low[v] > disc[u])
            {
                // (u, v) adalah bridge
            }
            if (low[v] >= disc[u])
            {
                // u adalah articulation point
            }
            low[u] = min(low[u], low[v]);
        }
        else if (v != parent)
        {
            low[u] = min(low[u], disc[v]);
        }
    }
}

dfs(root, -1);
// Special case
if (child[root] < 2)
{
    // root bukan articulation point
}
else
{
    // root adalah articulation point
}
/**
 * Author: Kevin
 * Date: 2016-01-14
 * License: CC0
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal
 * subtree that contains all the nodes by adding all (at most $|S|-1$)
 * pairwise LCA's and compressing edges.
 * Returns root of the virtual adjacency.
 * Time: $O(|S| \log |S|)$
 * Status: -
 */
#pragma once

#include "LCA.h"
vector<int> vAdj[MX]; // Store the adjacency
int virtualize(const vector<int> &query)
{
    if (query.size() == 0) return -1;
 
    vector<int> vt = query;
    sort(vt.begin(), vt.end(), [&](int a, int b) { return ST[a] < ST[b]; });
    for (int i = 1; i < query.size(); i++)vt.push_back(LCA(vt[i], vt[i - 1]));
    sort(vt.begin(), vt.end(), [&](int a, int b) { return ST[a] < ST[b]; });
    vt.erase(unique(vt.begin(), vt.end()), vt.end());
         
    for (auto v : vt) vAdj[v].clear(); // reset vAdj
    for (int i = 1; i < vt.size(); i++) vAdj[LCA(vt[i], vt[i - 1])].push_back(vt[i]);
    return vt[0]; //root
}

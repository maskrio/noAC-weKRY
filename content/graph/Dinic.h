/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
#pragma once

struct Dinic{
    using F = long long;
    struct Edge{
        int to;
        F flo, cap;
    };
    int N;
    vector<Edge> eds;
    vector<vector<int>> adj;
    vector<int> lev;
    vector<vector<int>::iterator> cur;

    void init(int _N)
    {
        N = _N;
        adj.assign(N,{});
        cur.assign(N,{});
    }

    void ae(int u, int v, F cap, F rcap=0)
    {
        adj[u].push_back((int)eds.size());
        eds.push_back({v,0,cap});
        adj[v].push_back((int)eds.size());
        eds.push_back({u,0,rcap});
    }

    bool bfs(int s , int t)
    {
        lev.assign(N,-1);
        for(int i = 0 ; i <N;i++)
        {
            cur[i]=adj[i].begin();
        }
        queue<int> q;
        q.push(s);
        lev[s]=0;
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(int e: adj[u])
            {
                const Edge &E = eds[e];
                if(lev[E.to]<0 && E.flo<E.cap)
                {
                    lev[E.to]=lev[u]+1;
                    q.push(E.to);
                }
            }
        }
        return lev[t]>=0;
    }

    F dfs(int v, int t, F flo)
    {
        if(v==t)
        {
            return flo;
        }
        for(;cur[v]!=adj[v].end();++cur[v])
        {
            Edge &E  =eds[*cur[v]];
            if(lev[E.to]!=lev[v]+1||E.flo==E.cap)
            {
                continue;
            }
            F df = dfs(E.to,t,min(flo, E.cap-E.flo));
            if(df)
            {
                E.flo+=df;
                eds[*cur[v]^1].flo-=df;
                return df;
            }
        }
        return 0;
    }

    F maxFlow(int s, int t)
    {
        F tot = 0;
        while(bfs(s,t))
        {
            while(F df = dfs(s,t,numeric_limits<F>::max()))
            {
                tot+=df;
            }
        }
        return tot;
    }
};
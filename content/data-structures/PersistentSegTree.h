/**
 * Author: worthytacos
 * Date: 2026-10-21
 * License: CC0
 * Source: folklore
 * Description: Persistent segment tree supporting point updates (sum and count),
 * range-sum queries, and sum of the largest k elements. Each update creates
 * a new version while preserving previous versions. Supports copying a version.
 * Time is O(log N) per update/query/copy, Space is O(log N) per update, O(1) per copy
 */
 
struct SegmentTree{
    struct Node{
        int sum = 0, cnt = 0, l = 0, r = 0;
    };

    int N, timer = 1;
    vector<Node> tree;
    
    SegmentTree(int n, int siz) : N(n), tree(siz) {};
    
    Node join(int l, int r){
        return Node({tree[l].sum + tree[r].sum, tree[l].cnt + tree[r].cnt, l,r});
    }
 
    int upd(int v, int tl, int tr, int pos, int val, int cnt){
        if (tl == tr){
            tree[timer] = {tree[v].sum + val,tree[v].cnt + cnt,0,0};
            return timer++;
        }
        int tm = (tl+tr)/2;
        if(pos <= tm) tree[timer] = join(upd(tree[v].l,tl,tm,pos,val,cnt), tree[v].r);
        else tree[timer] = join(tree[v].l, upd(tree[v].r,tm+1,tr,pos,val,cnt));
        return timer++;
    }
    // SUM OF THE BIGGEST K elements, walk example
    int ask(int v, int tl, int tr, int k){
        if(tl == tr){
            int get = min(k, tree[v].cnt);
            return get * tl;
        }
        // Check right first
        int tm = (tl+tr)/2;
        int rightCnt = tree[tree[v].r].cnt, rightSum = tree[tree[v].r].sum;
        
        if(rightCnt >= k) return ask(tree[v].r, tm+1, tr, k); // belongs there
        return ask(tree[v].l, tl, tm, k - rightCnt) + rightSum; // belongs left a bit
    }
    int query(int v, int tl, int tr, int ql, int qr){
        if(qr < tl || tr < ql) return 0;
        if(ql <= tl && tr <= qr) return tree[v].sum;
        int tm = (tl+tr)/2;
        return query(tree[v].l, tl, tm, ql, qr) + query(tree[v].r, tm+1, tr, ql, qr);
    }
    int cpy(int root) {
        tree[timer] = tree[root]; 
        return timer++;
    }
    int query(int root, int l, int r){
        return query(root, 1, N, l, r);
    }
    int upd(int root, int pos, int val, int cnt) {
        return upd(root,1,N, pos,val,cnt);
    }
    int ask(int v, int k){
        return ask(v, 1,N,k);
    }
};
// SegmentTree ST(mxN, mxN * (2 + __lg(mxN)));
// int root = 0; vector<int> roots = {root};    
// for(auto b : A)
// {
//     root = ST.upd(root, 1*b, b, 1);
// }
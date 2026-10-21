/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: Lazy implicit treap (sequence with log-time
 *  split/merge), with lazy reverse (flip) and per-value counts
 *  (cnt); edit the LAZY / AGG parts for other things.
 *  split(t,l,r,k): l = first k elements of t, r = the rest.
 *  merge(t,l,r): t = l followed by r.
 *  Keep the whole tree in a pnode root. root is only valid
 *  after a merge assigns it; after a split it still points
 *  at one of the two pieces, so merge back before using it.
 * Time: $O(\log N)$
 * Usage: pnode root = 0, L, M, R;
 *  merge(root, root, new Node(x)); // push_back
 *  // range [a,b]: cut out, use, put back
 *  split(root, L, M, a); split(M, M, R, b-a+1);
 *  M->flip ^= 1; // reverse   M->cnt[c] // count of c
 *  merge(root, L, M); merge(root, root, R);
 *  // insert x at p
 *  split(root, L, R, p); merge(L, L, new Node(x));
 *  merge(root, L, R);
 *  // erase at p
 *  split(root, L, M, p); split(M, M, R, 1);
 *  merge(root, L, R);
 * Status: stress-tested
 */
#pragma once

const int D = 10; // AGG: values in [0, D)

struct Node {
	int val, prio, sz = 1;
	bool flip = false; // LAZY: pending reverse
	int cnt[D] = {}; // AGG: cnt[c] = number of c in subtree
	Node *l = 0, *r = 0;
	Node(int x) : val(x), prio((int)rng()) { cnt[x] = 1; }
};
typedef Node* pnode;

int getsz(pnode t) { return t ? t->sz : 0; }

void push(pnode t) { // LAZY
	if (t && t->flip) {
		swap(t->l, t->r); t->flip = false;
		if (t->l) t->l->flip ^= 1;
		if (t->r) t->r->flip ^= 1;
	}
}

void pull(pnode t) {
	if (!t) return;
	t->sz = 1 + getsz(t->l) + getsz(t->r);
	rep(i,0,D) t->cnt[i] = (t->l ? t->l->cnt[i] : 0)
		+ (t->r ? t->r->cnt[i] : 0); // AGG
	t->cnt[t->val]++;
}

void split(pnode t, pnode &l, pnode &r, int k) {
	if (!t) { l = r = 0; return; }
	push(t);
	if (getsz(t->l) < k)
		split(t->r, t->r, r, k - getsz(t->l) - 1), l = t;
	else split(t->l, l, t->l, k), r = t;
	pull(t);
}

void merge(pnode &t, pnode l, pnode r) {
	push(l); push(r);
	if (!l || !r) t = l ? l : r;
	else if (l->prio > r->prio) merge(l->r, l->r, r), t = l;
	else merge(r->l, l, r->l), t = r;
	pull(t);
}

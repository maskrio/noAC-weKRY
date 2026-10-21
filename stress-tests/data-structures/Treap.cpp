#include "../utilities/template.h"

mt19937_64 rng(3);
#include "../../content/data-structures/Treap.h"

void dfs(pnode t, vi &out) {
	if (!t) return;
	push(t); dfs(t->l, out);
	out.push_back(t->val); dfs(t->r, out);
}

int main() {
	mt19937 g(5);
	rep(it,0,300) {
		pnode root = 0, L, M, R; vi v; int n = 1 + g() % 60;
		rep(i,0,n) {
			int x = g() % D;
			merge(root, root, new Node(x)); v.push_back(x);
		}
		rep(q,0,200) {
			if (g() % 4 == 0) { // insert example
				int p = g() % (n+1), x = g() % D;
				split(root, L, R, p); merge(L, L, new Node(x));
				merge(root, L, R);
				v.insert(v.begin()+p, x); n++;
			}
			if (n > 1 && g() % 4 == 0) { // erase example
				int p = g() % n;
				split(root, L, M, p); split(M, M, R, 1);
				merge(root, L, R);
				v.erase(v.begin()+p); n--;
			}
			int a = g() % n, b = g() % n, c = g() % D;
			if (a > b) swap(a, b);
			split(root, L, M, a); split(M, M, R, b-a+1);
			if (g() % 2) {
				M->flip ^= 1;
				reverse(v.begin()+a, v.begin()+b+1);
			} else {
				assert(M->cnt[c] ==
					count(v.begin()+a, v.begin()+b+1, c));
			}
			merge(root, L, M); merge(root, root, R);
			assert(getsz(root) == n);
		}
		vi got;
		dfs(root, got);
		assert(got == v);
	}
	cout<<"Tests passed!"<<endl;
}

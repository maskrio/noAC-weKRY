#include "../utilities/template.h"

#include "../../content/strings/SuffixAutomaton.h"

int main() {
	mt19937 g(7);
	auto rs = [&](int n, int k) {
		string s;
		rep(i,0,n) s += char('a' + (int)(g() % k));
		return s;
	};
	rep(it,0,3000) {
		int k = 2 + (int)(g() % 2), n = 1 + (int)(g() % 25);
		string a = rs(n, k), b = rs(1 + (int)(g() % 25), k);
		SAM S; S.build(a); S.calcCnt();
		set<string> ds;
		rep(i,0,n) rep(j,1,n-i+1) ds.insert(a.substr(i, j));
		assert(S.distinct() == (ll)ds.size());
		for (auto& t : ds) {
			int v = S.go(t);
			assert(v >= 0);
			int c = 0;
			for (size_t i = 0; i + t.size() <= a.size(); i++)
				if (a.compare(i, t.size(), t) == 0) c++;
			assert(S.s[v].cnt == c);
			assert(S.s[v].pos - sz(t) + 1 == (int)a.find(t));
		}
		string q = rs(1 + (int)(g() % 6), k);
		if (!ds.count(q)) assert(S.go(q) == -1);
		int best = 0;
		rep(i,0,sz(b)) rep(j,1,sz(b)-i+1)
			if (ds.count(b.substr(i, j))) best = max(best, j);
		assert(S.lcs(b) == best);
	}
	cout<<"Tests passed!"<<endl;
}

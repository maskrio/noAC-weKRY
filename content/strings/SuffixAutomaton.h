/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Suffix automaton of a string over 'a'..'z'.
 *  Every substring is a path from the root. link = suffix
 *  link, len = longest string of the state, cnt = occurrences,
 *  pos = first end index.
 * Time: build $O(nA)$, calcCnt $O(n\log n)$, go $O(m)$,
 *  distinct $O(n)$, lcs $O(m)$. Memory $O(nA)$.
 * Usage: SAM S; S.build(a); S.calcCnt(); // calcCnt for cnt
 *  S.distinct(); S.lcs(b); // b = other string
 *  int v = S.go(t); // -1 if t is not a substring of a
 *  S.s[v].cnt; // occurrences of t
 *  S.s[v].pos - sz(t) + 1; // first start index of t
 * Status: stress-tested
 */
#pragma once

const int A = 26; // alphabet 'a'..'z'

struct SAM {
	struct St {
		int len = 0, link = -1, cnt = 0, pos = 0, nxt[A] = {};
	}; // nxt == 0 means no edge (nothing points to the root)
	vector<St> s{1}; // s[0] = root
	int last = 0;

	// amortized O(1) walk + O(A) per new state
	void extend(char ch) {
		int c = ch - 'a', cur = sz(s), p = last;
		s.emplace_back();
		s[cur].len = s[last].len + 1;
		s[cur].cnt = 1; // this prefix ends here
		s[cur].pos = s[cur].len - 1; // first end index
		for (; p != -1 && !s[p].nxt[c]; p = s[p].link)
			s[p].nxt[c] = cur;
		if (p == -1) s[cur].link = 0;
		else {
			int q = s[p].nxt[c];
			if (s[p].len + 1 == s[q].len) s[cur].link = q;
			else { // split q: clone has the shorter strings
				int cl = sz(s);
				s.push_back(s[q]); // copies nxt, link, pos
				s[cl].len = s[p].len + 1;
				s[cl].cnt = 0;
				for (; p != -1 && s[p].nxt[c] == q;
						p = s[p].link)
					s[p].nxt[c] = cl;
				s[q].link = s[cur].link = cl;
			}
		}
		last = cur;
	}
	void build(const string& t) {
		for (char ch : t) extend(ch);
	}
	// O(n log n): call once after building, then
	// s[v].cnt = number of occurrences of state v
	void calcCnt() {
		vi o(sz(s));
		iota(all(o), 0);
		sort(all(o), [&](int a, int b) {
			return s[a].len < s[b].len; });
		for (int i = sz(o) - 1; i > 0; i--)
			s[s[o[i]].link].cnt += s[o[i]].cnt;
	}
	// O(|t|): state of t, or -1 if t is not a substring
	int go(const string& t) {
		int v = 0;
		for (char ch : t)
			if (!(v = s[v].nxt[ch - 'a'])) return -1;
		return v;
	}
	// v = go(t): occurrences = s[v].cnt (needs calcCnt),
	// first start index = s[v].pos - sz(t) + 1

	ll distinct() { // O(n): number of distinct substrings
		ll r = 0;
		rep(v,1,sz(s)) r += s[v].len - s[s[v].link].len;
		return r;
	}
	int lcs(const string& t) { // O(|t|): longest common substr
		int v = 0, l = 0, best = 0;
		for (char ch : t) {
			int c = ch - 'a';
			while (v && !s[v].nxt[c])
				v = s[v].link, l = s[v].len;
			if (s[v].nxt[c]) v = s[v].nxt[c], l++;
			best = max(best, l);
		}
		return best;
	}
};

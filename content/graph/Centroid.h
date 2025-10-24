/**
 * Author: Nando
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Centroid Decompose
 * Time: $O(N \log N)$
 * Status: -
 */
typedef long long ll;

ll n, m;
ll par[nax], removed[nax], sub[nax];
vector<vector<ll>> v(nax);
// Centroid
void get_sz(ll idx, ll bfr){
	sub[idx] = 1;
	for(auto y : v[idx]){
		if(y != bfr && !removed[y]){
			get_sz(y, idx);
			sub[idx] += sub[y];
		}
	}
}

ll find_centroid(ll idx){
	get_sz(idx, -1);
	ll tree = sub[idx];
	ll cek = 0;
	while(!cek){
		cek = 1;
		for(auto y : v[idx]){
			if(removed[y] || sub[y] > sub[idx]) continue;
			if(sub[y] > tree / 2){
				cek = 0;
				idx = y;
				break;
			}
		}
	}
	return idx;
}
void solve(ll idx){...}
ll built_centroid(ll idx){
	idx = find_centroid(idx);
    // Do smth here
    solve(idx);
	removed[idx] = 1;
	for(auto y : v[idx]){
		if(!removed[y]){
			ll nxt = built_centroid(y);
			par[nxt] = idx;
		}
	}
	return idx;
}
int main(){
	ios_base::sync_with_stdio(false); cout.tie(NULL); cin.tie(NULL);
	
	cin >> n >> m;
	for(ll i = 1; i < n; i++){
		ll x, y;
		cin >> x >> y;
		v[x].pb(y);
		v[y].pb(x);
	}
	built_centroid(1);
}
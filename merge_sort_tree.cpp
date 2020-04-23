const int N = 2e5 + 7;
 
vector <int> t[N << 2];
 
int a[N];
 
void build(int v, int l, int r) {
	if(l == r) {
		t[v].push_back(a[l]);
		return;
	}
	int mid = (l + r) >> 1;
	build(v * 2, l, mid);
	build(v * 2 + 1, mid + 1, r);
	merge(t[v * 2].begin(), t[v * 2].end(), t[v * 2 + 1].begin(), t[v * 2 + 1].end(), back_inserter(t[v]));
 
}
 
int query(int v, int l, int r, int L, int R, int lx, int rx) {
	if(l > R || r < L) return 0;
	if(l >= L && r <= R) return upper_bound(t[v].begin(), t[v].end(), rx) - lower_bound(t[v].begin(), t[v].end(), lx);
	int mid = (l + r) >> 1;
	return query(v * 2, l, mid, L, R, lx, rx) + query(v * 2 + 1, mid + 1, r, L, R, lx, rx);	
}

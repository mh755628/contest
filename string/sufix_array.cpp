struct SA{
	int n; vector <int> lcp, sa, rank;
	SA() {}
	SA(string str) : n(str.size()) {
		vector <int> p(n), c(n), cnt(max(1 << 8, n), 0);
		for(int i = 0; i < n; i++) cnt[str[i]]++;
		for(int i = 1; i < (1 << 8); i++) cnt[i] += cnt[i - 1];
		for(int i = 0; i < n; i++) p[--cnt[str[i]]] = i;
		int cc = 1; c[p[0]] = 0;
		for(int i = 1; i < n; i++) {cc += str[p[i]] != str[p[i - 1]]; c[p[i]] = cc - 1;}
		vector <int> pn(n), cn(n);
		for(int h = 0; (1 << h) < n; h++) {
			for(int i = 0; i < n; i++) pn[i] = (p[i] - (1 << h) + n) % n;
			fill(cnt.begin(), cnt.begin() + cc, 0);
			for(int i = 0; i < n; i++) cnt[c[pn[i]]]++;
			for(int i = 1; i < cc; i++) cnt[i] += cnt[i - 1];
			for(int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
			cc = 1; cn[p[0]] = 0;
			for(int i = 1; i < n; i++) {
				pair <int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]}, prv = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
				cc += (prv != cur);
				cn[p[i]] = cc - 1;
			}
			c.swap(cn);
		}
		sa = p; rank.resize(n); lcp.resize(n, 0);
		for(int i = 0; i < n; i++) rank[sa[i]] = i;
		int k = 0;
		for(int i = 0; i < n; i++) {
			if(rank[i] == n - 1) {k = 0; continue;}
			int j = p[rank[i] + 1];
			while(i + k < n && j + k < n && str[i + k] == str[j + k]) ++k;
			lcp[rank[i]] = k;
			if(k) --k;
		}
	}
};

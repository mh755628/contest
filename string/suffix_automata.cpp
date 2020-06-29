struct SA{
	struct state{
		int len, link, nxt[26];
		state() : len(0), link(-1) {
			fill(begin(nxt), end(nxt), 0);
		}
	};
	vector <state> d; int last = 0;
	SA() {
		d.push_back(state());
	}
	void add(char ch) { 
		int cur = d.size(); d.push_back(state());
		d[cur].len = d[last].len + 1;
		int p = last;
		while(p != -1 && !d[p].nxt[ch - 'a']) {
			d[p].nxt[ch - 'a'] = cur;
			p = d[p].link;
		}
		if(p == -1) {
			d[cur].link = 0;
		} else {
			int q = d[p].nxt[ch - 'a'];
			if(d[q].len == d[p].len + 1) {
				d[cur].link = q;
			} else {
				int clone = d.size(); d.push_back(d[q]);
				d[clone].len = d[p].len + 1;
				while(p != -1 && d[p].nxt[ch - 'a'] == q) {
					d[p].nxt[ch - 'a'] = clone;
					p = d[p].link;
				}
				d[cur].link = d[q].link = clone;
			}
		}
		last = cur;
	}
};

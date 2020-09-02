struct eertree{
	struct node{
		int nxt[26], len, link;
		node() : len(0), link(-1) {
			fill(nxt, nxt + 26, 0);
		}
	};
	vector <node> t; int p;
	eertree() : p(2) {
		t = vector <node> (3);
		t[1].len = -1;
		t[2].len = 0;
		t[2].link = t[1].link = 1;
	}
	int add(int pos, string &str) { 
		while(str[pos - t[p].len - 1] != str[pos]) p = t[p].link;
		int ch = str[pos] - 'a', x = t[p].link, r = 0;
		while(str[pos - t[x].len - 1] != str[pos]) x = t[x].link;
		if(!t[p].nxt[ch]) {
			r = 1;
			int y = t.size();
			t[p].nxt[ch] = y; t.push_back(node());
			t[y].len = t[p].len + 2;
			t[y].link = t[y].len == 1 ? 2 : t[x].nxt[ch];
		}
		p = t[p].nxt[ch];
		return r;
	}
};

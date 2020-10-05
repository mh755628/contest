struct DSU{
    vector <int> p, sz, stk;
    DSU(int n) {
        p.resize(n + 1); sz.resize(n + 1, 1);
        for(int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return (p[x] == x) ? p[x] : find(p[x]);
    }
    int merge(int x, int y) {
        if((x = find(x)) ^ (y = find(y))) {
            if(sz[x] > sz[y]) swap(x, y);
            p[x] = y;
            sz[y] += sz[x];
            stk.push_back(x);
            return 1;
        }
        return 0;
    }
    void roll_back(int t) {
        while(stk.size() > t) {
            int x = stk.back(); 
            stk.pop_back();
            sz[p[x]] -= sz[x];
            p[x] = x;
        }
    }
};

void update(int v, int l, int r, int L, int R, pair <int, int> e) {
    if(l > R || r < L) return;
    if(l >= L && r <= R) {
        edges[v].push_back(e);
        return;
    }
    int mid = (l + r) / 2;
    update(v * 2, l, mid, L, R, e);
    update(v * 2 + 1, mid + 1, r, L, R, e);
}

void build(int v, int l, int r, DSU &d) {
    int tm = d.stk.size(); 
    for(auto e: edges[v]) d.merge(e.first, e.second);
    if(l == r) {
        for(auto Q: query[l]) ans[Q.second] = d.sz[d.find(Q.first)];
    } else {
        int mid = (l + r) / 2;
        build(v * 2, l, mid, d);
        build(v * 2 + 1, mid + 1, r, d);
    }
    d.roll_back(tm);
}

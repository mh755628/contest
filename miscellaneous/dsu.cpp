struct DSU{
    vector <int> p, sz;
    DSU(int n = 0) : p(n + 1), sz(n + 1, 1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return (p[x] ^ x) ? (p[x] = find(p[x])) : p[x];
    }
    int operator [](int x) {
       return find(x);
    }
    int merge(int x, int y) {
        if((x = find(x)) ^ (y = find(y))) p[x] = y, sz[y] += sz[x];
        return y;
    }
};
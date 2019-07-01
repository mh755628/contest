const int inf = 0x3f3f3f3f, N = 3e5;

struct RMQ {
        vector <int> t;
        int n;
        RMQ(int n) : n(n) {
                t.resize(n << 1);
        }
        void build(int a[]) {
                for(int i = 0; i < n; i++) t[n + i] = a[i];
                for(int i = n - 1; i > 0; --i) t[i] = min(t[i << 1], t[i << 1 | 1]);
        }
        void modify(int p, int v) {
                for(t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
        }
        int query(int l, int r) { int res = inf;
                for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
                        if(l & 1) res = min(res, t[l++]);
                        if(r & 1) res = min(res, t[--r]);
                }
                return res;
        }
};

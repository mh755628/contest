struct SegTree {
        vector <int> t, lzy; int n;
        SegTree(int n) : n(n) {
                t.resize(4 * n + 7, 0);
                lzy.resize(4 * n + 7, 0);
        }
        void propagate(int cur, int l, int r) {
                if(lzy[cur]) {
                        t[cur] += lzy[cur] * (r - l + 1);
                        if(l != r) {
                                lzy[2 * cur] += lzy[cur];
                                lzy[2 * cur + 1] += lzy[cur];
                        } lzy[cur] = 0;
                }
        }
        void update(int cur, int l, int r, int L, int R, int val) {
                propagate(cur, l, r);
                if(l > R || r < L) return;
                if(l >= L && r <= R) {
                        lzy[cur] += val; propagate(cur, l, r);
                        return;
                }
                int mid = (l + r) >> 1;
                update(cur * 2, l, mid, L, R, val);
                update(cur * 2 + 1, mid + 1, r, L, R, val);
                t[cur] = t[cur * 2] + t[cur * 2 + 1];
        }
        int query(int cur, int l, int r, int L, int R) {
                propagate(cur, l, r);
                if(l > R || r < L) return 0;
                if(l >= L && r <= R) return t[cur];
                int mid = (l + r) >> 1;
                int res = query(cur * 2, l, mid, L, R) + query(cur * 2 + 1, mid + 1, r, L, R);
                t[cur] = t[cur * 2] + t[cur * 2 + 1];
                return res;
        }
};

struct Node {
    int l, r, val;
    Node() : l(0), r(0), val(1) {}
}t[N * 30];
 
int ptr, root[N];
 
void add(int cur, int ex, int l, int r, int pos, int val) {
    t[cur] = t[ex];
    if(l == r) {
        t[cur].val = val;
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) add(t[cur].l = ++ptr, t[ex].l, l, mid, pos, val);
    else           add(t[cur].r = ++ptr, t[ex].r, mid + 1, r, pos, val);
    t[cur].val = (1LL * t[t[cur].l].val * t[t[cur].r].val) % mod;
}
 
int query(int cur, int l, int r, int L, int R) {
    if(l > R || r < L) return 1;
    if(l >= L && r <= R) return t[cur].val;
    int mid = (l + r) >> 1;
    return (1LL * query(t[cur].l, l, mid, L, R) * query(t[cur].r, mid + 1, r, L, R)) % mod;
}


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct treap {
    struct node{
        int value = 0, priority = rng(), size = 1;
        node *l = NULL, *r = NULL;
        node(int x) : value(x) {}
    } *root = NULL;
 
    int size(node *v) {
        return !v ? 0 : v -> size;
    }
    void recalc(node *v) {
        if(!v) return;
        v -> size = size(v -> l) + size(v -> r) + 1;
    }
    node *merge(node *p, node *q) {
        if(!p || !q) return !p ? q : p;
        if(p -> priority < q -> priority) {
            p -> r = merge(p -> r, q);
            recalc(p);
            return p;
        } else {
            q -> l = merge(p, q -> l);
            recalc(q);
            return q;
        }
    }
    pair <node *, node *> split(node *v, int cnt) {
        if(!v) return {NULL, NULL};
        if(size(v -> l) >= cnt) {
            auto [p, q] = split(v -> l, cnt);
            v -> l = q;
            recalc(v);
            return {p, v};
        } else {
            auto [p, q] = split(v -> r, cnt - size(v -> l) - 1);
            v -> r = p;
            recalc(v);
            return {v, q};
        }
    }
    void insert(int x) {
        root = merge(root, new node(x));
    }
}; 

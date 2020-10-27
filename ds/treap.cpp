mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
struct treap {
    struct node{
        int value, priority = rng(), size = 1, lazy = 0;
        node *l = NULL, *r = NULL;
        node(int value = 0) : value(value) {
        }
    } *root = NULL;
 
    int size(node *v) {
        return (v == NULL) ? 0 : v -> size;
    }
    void recalc(node *v) {
        if(v)
            v -> size = size(v -> l) + size(v -> r) + 1;
    }
    void push(node *v) {
        if(v == NULL) return;
        if(v -> lazy) {
            swap(v -> l, v -> r);
            if(v -> l) (v -> l) -> lazy ^= 1;
            if(v -> r) (v -> r) -> lazy ^= 1;
        }
        v -> lazy = 0;
        recalc(v);
        return;
    }
    node *merge(node *p, node *q) {
        if(p == NULL || q == NULL) return (p == NULL) ? q : p;
        push(p);
        push(q);
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
        if(v == NULL) return {NULL, NULL};
        push(v);
        if(size(v -> l) >= cnt) {
            auto [p, q] = split(v -> l, cnt);
            v -> l = q;
            push(v);
            return {p, v};
        } else {
            auto [p, q] = split(v -> r, cnt - size(v -> l) - 1);
            v -> r = p;
            push(v);
            return {v, q};
        }
    }
    void insert(int x) {
        root = merge(root, new node(x));
    }
};

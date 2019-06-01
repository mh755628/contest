typedef long long LL;

struct Line {
    mutable LL m, b, p;
    bool operator<(const Line &o) const { return m < o.m; }
    bool operator<(const LL &x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> { // upper convex hull.
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    const LL inf = LLONG_MAX;
    LL div(LL a, LL b) { return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) {
            x->p = inf;
            return false;
        }
        if (x->m == y->m)
            x->p = x->b > y->b ? inf : -inf;
        else
            x->p = div(y->b - x->b, x->m - y->m);
        return x->p >= y->p;
    }
    void add(LL m, LL b) {
        auto z = insert({m, b, 0}), y = z++, x = y;
        while (isect(y, z))
            z = erase(z);
        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    LL query(LL x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.m * x + l.b;
    }
};

template <typename T, typename U>
struct LazySegmentTree {

    function <T(const T&, const T&)> Combine; //merge two segments
    function <T()> Default; //default value of a segment
    function <U()> Id; //identity element of the operation
    function <T(const T&, const U&, int l, int r)> Apply; //apply operation to a segment
    function <U(const U&, const U&)> Compose; //compose two operations

    int n;

    vector <T> data;
    vector <U> lazy;

    LazySegmentTree(
        int n, 
        function <T(const T&, const T&)>                Combine, 
        function <T()>                                  Default, 
        function <U()>                                  Id,
        function <T(const T&, const U&, int l, int r)>  Apply,
        function <U(const U&, const U&)>                Compose
    ):
        n(n),
        Combine(Combine), 
        Default(Default), 
        Id(Id), 
        Apply(Apply),
        Compose(Compose),
        data(vector <T> (n << 2, Default())), 
        lazy(vector <U> (n << 2, Id())) 
    {}
        
    void push(int v, int l, int r) {
        if(lazy[v] != Id()) {
            data[v] = Apply(data[v], lazy[v], l, r);
            if(l != r) {
                lazy[v << 1] = Compose(lazy[v << 1], lazy[v]);
                lazy[v << 1 | 1] = Compose(lazy[v << 1 | 1], lazy[v]);
            }
            lazy[v] = Id();
        }
    }

    void build(vector <T> &v) {
        build(1, 1, n, v);
    }

    void build(int v, int L, int R, vector <T> &val) {
        if(L == R) {
            data[v] = val[L];
            return;
        }
        int mid = (L + R) >> 1;
        build(v << 1, L, mid, val);
        build(v << 1 | 1, mid + 1, R, val);
        data[v] = Combine(data[v << 1], data[v << 1 | 1]);
    }

    void set(int pos, T val) {
        set(1, 1, n, pos, val);
    }

    void set(int v, int l, int r, int pos, T x) {
        push(v, l, r);
        if(l == r) {
            data[v] = x;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid)
            set(v << 1, l, mid, pos, x);
        else
            set(v << 1 | 1, mid + 1, r, pos, x);
        data[v] = Combine(data[v << 1], data[v << 1 | 1]);
    }

    void Update(int L, int R, U x) {
        Update(1, 1, n, L, R, x);
    }

    T Query(int L, int R) {
        return Query(1, 1, n, L, R);
    }

    void Update(int v, int l, int r, int L, int R, U x) {
        push(v, l, r);
        if(l > R or r < L)
            return;
        if(l >= L and r <= R) {
            lazy[v] = Compose(lazy[v], x);
            push(v, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        Update(v << 1, l, mid, L, R, x);
        Update(v << 1 | 1, mid + 1, r, L, R, x);
        data[v] = Combine(data[v << 1], data[v << 1 | 1]);
    }

    T Query(int v, int l, int r, int L, int R) {
        push(v, l, r);
        if(l > R or r < L)
            return Default();
        if(l >= L and r <= R)
            return data[v];
        int mid = (l + r) >> 1;
        return Combine(Query(v << 1, l, mid, L, R), Query(v << 1 | 1, mid + 1, r, L, R));
    }
};

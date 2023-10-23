//receives 0 indexed 
//calculates 1 indexed
template <typename T> 
struct SparseTable{
    using F = function<T(const T&, const T&)>;
    F f;
    vector <vector <T>> t;
    SparseTable(vector <T> a, F f) : f(f) {
        int n = a.size(), k = 31 - __builtin_clz(n);
        t = vector <vector <T>> (k + 1, vector <T> (n + 1));
        for(int i = 0; i < n; i++) t[0][i + 1] = a[i];
        for(int i = 1; i <= k; i++) {
            for(int j = 1; j + (1 << i) - 1 <= n; j++) {
                t[i][j] = f(t[i - 1][j], t[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    T query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return f(t[k][l], t[k][r - (1 << k) + 1]);
    }
};




template <typename T> 
struct SparseTable{
    using F = function<bool(const T&, const T&)>;
    F f;
    vector <T> a;
    vector <vector <int>> index;
    SparseTable(vector <T> a, F f) : a(a), f(f) {
        int n = a.size(), k = 31 - __builtin_clz(n);
        index = vector <vector <int>> (k + 1, vector <T> (n + 1));
        for(int i = 0; i < n; i++) index[0][i + 1] = i;
        for(int i = 1; i <= k; i++) {
            for(int j = 1; j + (1 << i) - 1 <= n; j++) {
                int p = index[i - 1][j], q = index[i - 1][j + (1 << (i - 1))];
                index[i][j] = (f(a[p], a[q]) ? p : q);
            }
        }
    }
    //Note: breaks ties by choosing smaller index
    T query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        int p = index[k][l], q = index[k][r - (1 << k) + 1];
        return (f(a[p], a[q]) ? p : q);
    }

    T query_value(int l, int r) {
        return a[query(l, r)];
    }
};
struct Tree {
    vector <vector <int>> adj;
    vector <int> st, en, lvl, sz, par;
    int ptr = 0;

    Tree(int n) : adj(n + 1) {
        st = en = lvl = sz = par = vector <int> (n + 1, 0);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p) {
        par[v] = p;
        sz[v] = 1;
        st[v] = ++ptr;
        lvl[v] = lvl[p] + 1;

        for(int u: adj[v]) {
            if(p ^ u) {
                dfs(u, v);
                sz[v] += sz[u];
            }
        }
        
        en[v] = ++ptr;
    }
};

struct Lca {
    vector <vector <int>> ancestor;
    vector <int> lvl;
    int k = 0;

    Lca(Tree &tree) : lvl(tree.lvl) {
        int n = tree.adj.size() - 1;
        while((1 << k) <= n) 
            k++;
        ancestor = vector <vector <int>> (k, vector <int> (n + 1, 0));

        for(int i = 1; i <= n; i++) { 
            ancestor[0][i] = tree.par[i];
        }
        
        for(int i = 1; i < k; i++) {
            for(int j = 1; j <= n; j++) {
                ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];
            }
        }
    }

    int lift(int v, int dis) {
        for(int i = k - 1; i >= 0; i--) {
            if(lvl[v] - (1 << i) >= dis) {
                v = ancestor[i][v];
            }
        }
        return v;
    }

    int lca(int u, int v) {
        if(lvl[u] > lvl[v]) 
            swap(u, v);
        
        int k = ancestor.size();
        v = lift(v, lvl[u]);

        for(int i = k - 1; i >= 0; i--) {
            if(ancestor[i][v] ^ ancestor[i][u]) {
                u = ancestor[i][u];
                v = ancestor[i][v];
            }
        }
        return u == v ? v : ancestor[0][v];
    }
};

struct HeavyLightDecomposition {
    vector <int> head, pos, lvl, par;
    int id = 0;

    HeavyLightDecomposition(Tree &tree) : lvl(tree.lvl), par(tree.par) {
        head = pos = vector <int> (tree.adj.size(), 0);
        dfs(1, 0, 1, tree);
    }

    void dfs(int v, int p, int h, Tree &tree) {
        head[v] = h;
        pos[v] = ++id;

        int mx = -1, bigChild = -1;
        for(int u: tree.adj[v]) {
            if(u ^ p and tree.sz[u] > mx) {
                mx = tree.sz[u];
                bigChild = u;
            }
        }
        
        if(~bigChild) 
            dfs(bigChild, v, h, tree);
        
        for(int u: tree.adj[v]) {
            if(u ^ p and u ^ bigChild) {
                dfs(u, v, u, tree);
            }
        }
    }

    int lca(int u, int v, Tree &tree) {
        while(head[u] ^ head[v]) {
            if(lvl[head[u]] < lvl[head[v]]) 
                swap(u, v);
            u = tree.par[head[u]];
        }
        return lvl[u] < lvl[v] ? u : v;
    }

    void pathUpdate(int u, int v, int val) {
        while(head[u] ^ head[v]) {
            if(lvl[head[u]] < lvl[head[v]]) 
                swap(u, v);
            // update(1, 1, n, pos[head[u]], pos[u], val);
            u = par[head[u]];
        }
        if(lvl[u] < lvl[v]) 
            swap(u, v);
        // update(1, 1, n, pos[v], pos[u], val);
    }

    template <typename T> 
    T pathQuery(int u, int v) {
        T res = 0;
        while(head[u] ^ head[v]) {
            if(lvl[head[u]] < lvl[head[v]]) 
                swap(u, v);
            // res += query(1, 1, n, pos[head[u]], pos[u]);
            u = par[head[u]];
        }
        if(lvl[u] < lvl[v]) 
            swap(u, v);
        // res += query(1, 1, n, pos[v], pos[u]);
        return res;
    }
};
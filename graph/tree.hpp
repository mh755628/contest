#include <bits/stdc++.h>
using namespace std;


struct Tree {
    vector <vector <int>> adj, anc;
    vector <int> tin, tout, depth, sz, parent, node_at, bigChild;
    int timer = 0, k = 0, n;
 
    Tree(int n) : adj(n + 1), n(n) {
        tin = tout = depth = sz = parent = node_at = vector <int> (n + 1, 0);
        bigChild = vector <int> (n + 1, -1);
    }
 
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    void dfs(int v, int p) {
        parent[v] = p;
        sz[v] = 1;
        tin[v] = ++timer;
        node_at[tin[v]] = v;
        depth[v] = depth[p] + 1;
 
        for(int u: adj[v]) {
            if(p ^ u) {
                dfs(u, v);
                sz[v] += sz[u];
 
                if(bigChild[v] == -1 or sz[u] > sz[bigChild[v]]) {
                    bigChild[v] = u;
                }
            }
        }
        
        tout[v] = timer;
    }

    void init_lca() {
        int n = adj.size() - 1;
        k = __lg(n) + 1;
        anc = vector <vector <int>> (k, vector <int> (n + 1, 0));

        for(int i = 1; i <= n; i++) { 
            anc[0][i] = parent[i];
        }
        
        for(int i = 1; i < k; i++) {
            for(int j = 1; j <= n; j++) {
                anc[i][j] = anc[i - 1][anc[i - 1][j]];
            }
        }
    }

    int lift(int v, int dis) {
        for(int i = k - 1; i >= 0; i--) {
            if(depth[v] - (1 << i) >= dis) {
                v = anc[i][v];
            }
        }
        return v;
    }

    int lca(int u, int v) {
        if(depth[u] > depth[v]) 
            swap(u, v);
        
        int k = anc.size();
        v = lift(v, depth[u]);

        for(int i = k - 1; i >= 0; i--) {
            if(anc[i][v] ^ anc[i][u]) {
                u = anc[i][u];
                v = anc[i][v];
            }
        }
        return u == v ? v : anc[0][v];
    }

    void print_tree(int v, int p, string prefix = "", bool isLast = true) {
        cerr << prefix;
        cerr << (isLast ? "└── " : "├── ");
        cerr << v << endl;
        // cerr << v << " (tin=" << tin[v] << ", tout=" << tout[v] << ", sz=" << sz[v] << ")\n";

        vector<int> children;
        for (int u : adj[v]) {
            if (u != p) children.push_back(u);
        }

        for (int i = 0; i < (int)children.size(); i++) {
            int u = children[i];
            bool last = (i + 1 == (int)children.size());
            print_tree(u, v, prefix + (isLast ? "    " : "│   "), last);
        }
    }
 
};
 
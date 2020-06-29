struct SCC{
    const static int N = 2000 + 7;

    vector <int> adj[N], r_adj[N];
    int V, visit[N], cnt, color[N];
    stack <int> stk;

    SCC(int V) : V(V), cnt(0) {
        memset(visit, 0, sizeof visit);
    }

    void add_edge(int x, int y) {
        adj[x].push_back(y);
        r_adj[y].push_back(x);
    }

    void dfs(int u) { 
        visit[u] = true;
        for(int v: adj[u]) if(!visit[v]) {
            dfs(v);
        }
        stk.push(u);
    }

    void dfs(int u, int id) {
        visit[u] = false; color[u] = id;
        for(int v: r_adj[u]) if(visit[v]) {
            dfs(v, id);
        }
    }


    int get() {
        for(int i = 1; i <= V; i++) if(!visit[i]) {
            dfs(i);
        }
        while(stk.size()) {
            int v = stk.top(); stk.pop(); 
            if(visit[v]) {
                dfs(v, ++cnt);
            }
        } 
        return cnt;
    }


};

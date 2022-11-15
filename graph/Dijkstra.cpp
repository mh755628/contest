namespace graph{
    using T = long long;
	const T inf = 0x3f3f3f3f3f3f3f3f;
    using pii = pair<T, int>;
	vector <vector<pii> > adj;
    vector <int> par;
 
	void init(int n) {
		adj.resize(n + 1);
        par.resize(n + 1, -1);
	}
    
	void add_edge(int u, int v, T w) {
		adj[u].push_back(make_pair(w, v));
		adj[v].push_back(make_pair(w, u));
	}
 
	vector <T> dijkstra(int s) {
		vector <T> d(adj.size(), inf);
		priority_queue <pii, vector <pii>, greater <pii> > pq;
		pq.push(make_pair(d[s] = 0, s));
		while(!pq.empty()) {
			auto [x, u] = pq.top(); 
            pq.pop();
            if(x != d[u]) 
                continue;
			for(auto [w, v]: adj[u]) if(d[u] + w < d[v]) {
				d[v] = d[u] + w;
                par[v] = u;
				pq.push(make_pair(d[v], v));
			}
		}
		return d;
	}

    vector <int> getPath(int v) {
        vector <int> path;
        do {
            path.push_back(v);
            v = par[v];
        } while(v != -1);
        reverse(path.begin(), path.end());
        return path;
    }
}
 
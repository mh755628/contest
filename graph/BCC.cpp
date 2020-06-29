


const int N = 300003;
 
vector <int> adj[N];
 
int dis[N], low[N], col[N], ins[N], t, id;
 
stack <int> stk;
 
void BCC(int u, int p) {
 
    dis[u] = low[u] = ins[u] = ++t; stk.push(u);
 
    for(int v: adj[u]) {
        if(!dis[v]) {
            BCC(v, u);
            low[u] = min(low[u], low[v]);
        } else if(ins[v] && p != v)
            low[u] = min(low[u], dis[v]);
    }
 
    if(dis[u] == low[u]) {
        ++id; int v;
        do {
            v = stk.top(); stk.pop();
            ins[v] = 0; col[v] = id;
        } while(v != u);
    }
}

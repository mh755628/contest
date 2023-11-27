struct SCC{
    int n, componentCount = 0;
    vector <vector <int>> adjacencyList, reverseAdjacencyList;
    vector <int> isVisited, componentId;
    stack <int> stk;
 
    SCC(int n) : n(n) {
        adjacencyList = reverseAdjacencyList = vector <vector <int>> (n + 1);
        isVisited = componentId = vector <int> (n + 1, 0);
    }
 
    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        reverseAdjacencyList[v].push_back(u);
    }
 
    void dfs(int u) { 
        isVisited[u] = true;
        for(int v: adjacencyList[u]) if(!isVisited[v]) {
            dfs(v);
        }
        stk.push(u);
    }
 
    void dfs(int u, int id) {
        isVisited[u] = false; 
        componentId[u] = id;
        for(int v: reverseAdjacencyList[u]) if(isVisited[v]) {
            dfs(v, id);
        }
    } 
 
    int init() {
        for(int i = 1; i <= n; i++) { 
            if(!isVisited[i]) {
                dfs(i);
            }
        }
        while(not stk.empty()) {
            int v = stk.top(); 
            stk.pop(); 
            if(isVisited[v]) {
                dfs(v, ++componentCount);
            }
        } 
        return componentCount;
    }

    int getId(int u) {
        return componentId[u];
    }
 
    int operator[](int v) {
        return componentId[v];
    }

    vector <vector <int>> getCondenstaionGraph() {
        vector <vector <int>> ret(n + 1);
        for(int i = 1; i <= n; i++) {
            for(int j: adjacencyList[i]) {
                if(getId(i) ^ getId(j)) {
                    ret[componentId[i]].push_back(componentId[j]);
                }
            }
        }
        return ret;
    }
};

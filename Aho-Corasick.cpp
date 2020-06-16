struct AC {
    static const int K = 1 << 8;
    struct node {
        int nxt[K], go[K], link, leaf, par; 
        char pch;
        node(int par = -1, char pch = '$') : par(par), pch(pch) {
            fill(begin(nxt), end(nxt), -1);
            fill(begin(go), end(go), -1);
            leaf = false;
            link = -1;
        }
    };
    vector <node> tree;
    AC() {
        tree.resize(1);
    }
    int add(string str) {
        int ptr = 0;
        for(auto ch: str) {
            if(tree[ptr].nxt[ch] == -1) {
                tree[ptr].nxt[ch] = tree.size();
                tree.push_back(node(ptr, ch));
            }
            ptr = tree[ptr].nxt[ch];
        }
        tree[ptr].leaf = true;
        return ptr;
    }

    int get_link(int v) {
        if(tree[v].link == -1) {
            if(v == 0 || tree[v].par == 0) {
                tree[v].link = 0;
            } else {
                tree[v].link = go(get_link(tree[v].par), tree[v].pch);
            }
        }
        return tree[v].link;
    }
    int go(int v, char ch) {
        if(tree[v].go[ch] == -1) {
            if(tree[v].nxt[ch] != -1) {
                tree[v].go[ch] = tree[v].nxt[ch];
            } else {
                tree[v].go[ch] = (v == 0) ? 0 : go(get_link(tree[v].par), ch);
            }
        }
        return tree[v].go[ch];
    }

};

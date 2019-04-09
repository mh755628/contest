#include <bits/stdc++.h>
using namespace std;


typedef int T;

T merge(T a,T b) {return a + b;}

void construct(vector<T>&tree,vector<T>&arr,T n){tree.resize(2*n);for(T i=0;i<n;i++)tree[n+i]=arr[i];for(T i=n-1;i;i--)tree[i]=merge(tree[i<<1],tree[i<<1|1]);}

T query(vector<T>&tree,T l,T r,T n){T m=0;for(l+=n,r+=n;l<=r;l=(l+1)>>1,r=(r-1)>>1){if(l&1)m=merge(m,tree[l]);if(!(r&1))m=merge(m,tree[r]);}return m;}

T main() {
        int n; cin >> n;
        vector <int> v(n, 0), tree;
        for(int i = 0; i < n; i++) {
                cin >> v[i];
        }
        construct(tree, v, n);
        int q; cin >> q;
        for(int i = 1; i <= q; i++) {
                int l, r; cin >> l >> r;
                cout << query(tree, l, r, n) << endl;
        }
}

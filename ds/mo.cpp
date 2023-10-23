namespace mo{
    const int magic = 350;

    template <typename T> inline void add(T x) {
        
    }
    template <typename T> inline void del(T x) {

    }

    struct query{
        int l, r, b, i; 
        void in(int j) {
            i = j;
            cin >> l >> r;
            b = l / magic;
        }
        bool operator<(const query &a) const {
            return ((b ^ a.b) ? b < a.b : ((b & 1) ? r < a.r : r > a.r));
        }
    };

    template <typename T> vector <T> init(int m) {
        int c = 0;
        vector <T> b(m + 1);
        vector <query> Q(m);
        for(auto &q: Q) q.in(++c);
        sort(Q.begin(), Q.end());

        int L = 1, R = 1;
        add(1);

        for(const auto &[l, r, c, i]: Q) {
            while(L < l) del(L++);
            while(L > l) add(--L);
            while(R > r) del(R--);
            while(R < r) add(++R);
        }

        return b;
    }
}
struct BitSet {
     typedef unsigned long long ULL;
     vector <ULL> t; int l;
     BitSet() {}
     BitSet(int n) {
        l = (n + 63) / 64;
        t.resize(l, 0);
     }
     void resize(int n) {
        l = (n + 63) / 64;
        t.resize(l, 0);
    }
    BitSet operator &(BitSet a) {
        BitSet x(l * 64);
        for(int i = 0; i < l; i++) x.t[i] = t[i] & a.t[i];
        return x;
    }
    BitSet operator |(BitSet a) {
        BitSet x(l * 64);
        for(int i = 0; i < l; i++) x.t[i] = t[i] | a.t[i];
        return x;
    }
    BitSet operator ^(BitSet a) {
        BitSet x(l * 64);
        for(int i = 0; i < l; i++) x.t[i] = t[i] ^ a.t[i];
        return x;
    }
    int count() {
        int res = 0;
        for(int i = 0; i < l; i++) res += __builtin_popcount(t[i]);
        return res;
    }
    int chk(int idx) {
        return t[idx / 64] & (1LL << (idx % 64));
    }
    int reset() {
        fill(t.begin(), t.end(), 0);
    }
    int set(int idx) {
        t[idx / 64] |= (1LL << (idx % 64));
    }
    void print() {
        for(int i = 0; i < l; i++) {
            for(int j = 0; j < 64; j++) {
                cout << ((t[i] >> j) & 1LL);
            }
        }
    }
};

struct Hash {
    int len, base; long long mod; vector <int> p, h;
    Hash(int len, int base, int mod) : len(len), base(base), mod(mod) {
        p.resize(len + 1, 0); h.resize(len + 1, 0); p[0] = 1;
        for(int i = 1; i <= len; i++) {
            p[i] = (1LL * p[i - 1] * base) % mod;
        }
    }
    void init(string &str){
        for(int i = 1; i <= len; i++) {
            h[i] = (1LL * h[i - 1] * base + (int)str[i - 1]) % mod;
        }
    }
    int substr(int l, int r) {
        return (h[r] - (1LL * h[l - 1] * p[r - l + 1]) % mod + mod) % mod;
    }
};

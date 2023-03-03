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


struct Hash{
    const static int mod = 1e9 + 9, base = 163;
    int val = 0, len = 0;
 
    Hash(char ch = '#') {
        val = ch;
        len = 1;
    }
 
    static int pow(int n) {
        static vector<int> p = {1};
        while(p.size() <= n) {
            p.push_back(1LL * p.back() * base % mod);
        }
        return p[n];
    }
 
    Hash operator + (const Hash &h) const {
        Hash ret;
        ret.val = (1LL * val * h.pow(h.len) + h.val) % mod;
        ret.len = len + h.len;
        return ret;
    }
 
    bool operator == (const Hash &h) const {
        return val == h.val and len == h.len;
    }
 
    bool operator < (const Hash &h) const {
        if(len != h.len) return len < h.len;
        return val < h.val;
    }
};

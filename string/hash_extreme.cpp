typedef __int128_t LL;

struct Hash {
    LL mod = 1000000000000000003, base = 163;
    vector <LL> p, h;
    int len;
    Hash(string str = "") : len(str.size()) { 
        p = vector <LL> (len + 1, 1);
        h = vector <LL> (len + 1, 0);
        for(int i = 1; i <= len; i++) {
            p[i] = p[i - 1] * base % mod;
            h[i] = (h[i - 1] * base + (LL)str[i - 1]) % mod;
        }
    }
    LL substr(int l, int r) {
        return (h[r] - (h[l - 1] * p[r - l + 1]) % mod + mod) % mod;
    }
};

struct P {
    Hash a, b; int len;
    P(string str = "") : len(str.size()) {
        a = Hash(str);
        reverse(str.begin(), str.end());
        b = Hash(str);
    }
    bool is_pallindrome(int l, int r) {
        return a.substr(l, r) == b.substr(len - r + 1, len - l + 1);
    }
};






struct Hash {
    const int K = 5;
    LL mod[5] = {1000000000000000003, 1000000000000037, 1000000000039, 1000000007, 1000003}, base[5] = {211, 307, 401, 503, 163};
    vector <vector <LL> > p, h;
    int len;
    Hash(string str = "") : len(str.size()) { 
        p = vector <vector <LL> > (K, vector <LL> (len + 1, 1));
        h = vector <vector <LL> > (K, vector <LL> (len + 1, 0));
        for(int i = 1; i <= len; i++) {
            for(int j = 0; j < K; j++) {
                p[j][i] = p[j][i - 1] * base[j] % mod[j];
                h[j][i] = (h[j][i - 1] * base[j] + (LL)str[i - 1]) % mod[j];
            }
        }
    }
    vector <LL> substr(int l, int r) {
        vector <LL> ans(K, 0);
        for(int i = 0; i < K; i++) {
            ans[i] = (h[i][r] - (h[i][l - 1] * p[i][r - l + 1]) % mod[i] + mod[i]) % mod[i];
        }
        return ans;
    }
};

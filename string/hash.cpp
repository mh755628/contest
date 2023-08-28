template <typename T, typename U, T mod, T base>
struct Hash {
    T val = 0, len = 0;
    Hash(T val = 0, int len = 0) {
        this->val = val;
        this->len = len;
    }
    static T pwr(T m) {
        static vector <T> p = {1};
        while(p.size() <= m) p.push_back((U)p.back() * base % mod);
        return p[m];
    }
    Hash operator + (const Hash &h) const {
        return Hash(((U)val * pwr(h.len) + h.val) % mod, len + h.len);
    }
    Hash operator - (const Hash &h) const {
        return Hash((val - (U)h.val * pwr(len - h.len) % mod + mod) % mod, len - h.len);
    }
    bool operator == (const Hash &h) const {
        return val == h.val and len == h.len;
    }
    friend ostream &operator << (ostream &os, const Hash &h) {
        return os << "[" << h.val << ", " << h.len << "]";
    }
};

using h = Hash <int, long long, (int)(1e9 + 9), 163>;


struct String {
    vector <h> hsh;
    String(string str = "") {
        int n = str.size();
        hsh.resize(n + 1);
        for(int i = 0; i < n; i++) {
            hsh[i + 1] = hsh[i] + h(str[i], 1);
        }
    }
    h substr(int l, int r) {
        return hsh[r] - hsh[l - 1];
    }
};

struct Pallindrome {
    String F, B;
    int len;
    Pallindrome(string str = "") {
        len = str.size();
        F = String(str);
        reverse(str.begin(), str.end());
        B = String(str);
    }
    pair <h, h> substr(int l, int r) {
        return {F.substr(l, r), B.substr(len - r + 1, len - l + 1)};
    }
};

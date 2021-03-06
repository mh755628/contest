template <int mod = 1000000007>
struct modint{
    int x;
    modint(int y = 0) : x((y % mod + mod) % mod) { }
    friend modint operator^(modint a, long long b) {
        modint r = 1;
        for(; b; b >>= 1, a *= a) if(b & 1) r *= a;
        return r;
    }
    friend modint operator-(modint a) {return modint(0) - a;}
    friend modint operator!(modint a) {return a ^ (mod - 2);}
    modint& operator/=(modint const& b) {return *this *= !b;}
    friend modint operator+(modint a, modint const& b) {return a += b;}
    friend modint operator-(modint a, modint const& b) {return a -= b;}
    friend modint operator*(modint a, modint const& b) {return a *= b;}
    friend modint operator/(modint a, modint const& b) {return a /= b;}
    friend ostream& operator<<(ostream& os, modint const& a) {return os << a.x;}
    friend bool operator!=(modint const& a, modint const& b) {return a.x ^ b.x;}
    friend bool operator==(modint const& a, modint const& b) {return !(a != b);}
    modint& operator*=(modint const& b) {x = 1LL * x * b.x % mod; return *this;}
    modint& operator+=(modint const& b) {x += b.x; x = (x >= mod) ? x - mod : x;return *this;}
    modint& operator-=(modint const& b) {x = x >= b.x ? x - b.x : x - b.x + mod;return *this;}
};

using mint = modint <998244353>;

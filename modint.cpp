template <int mod = 1000000007>
struct modint{
    int x;
    modint(int y = 0) : x(y % mod) { x = x < 0 ? x + mod : x;}
    modint& operator+=(modint const& b) {x += b.x; x = (x >= mod) ? x - mod : x;return *this;}
    modint& operator-=(modint const& b) {x = x >= b.x ? x - b.x : x - b.x + mod;return *this;}
    modint& operator*=(modint const& b) {x = 1LL * x * b.x % mod;return *this;}
    friend ostream& operator<<(ostream& os, modint const& a) {return os << a.x;}
    friend modint operator^(modint a, long long b) {
        modint res = 1;
        for(int i = b; i; i >>= 1, a *= a) if(i & 1) res *= a;
        return res;
    }
    friend modint operator!(modint a) {return (a ^ (mod - 2));}
    modint& operator/=(modint const& b) {return *this *= (!b);}
    friend modint operator+(modint a, modint const& b) {return a += b;}
    friend modint operator-(modint a, modint const& b) {return a -= b;}
    friend modint operator*(modint a, modint const& b) {return a *= b;}
    friend modint operator/(modint a, modint const& b) {return a /= b;}
    friend modint operator-(modint a) {return 0 - a;}
};

template <typename T> struct point {
    T x, y;
    point(T x = 0, T y = 0) : x(x), y(y) {}
    point& operator+=(point const& a) {x += a.x; y += a.y; return *this;}
    friend point operator+(point a, point b) {return a += b;}
    point& operator-=(point const& a) {x -= a.x; y -= a.y; return *this;}
    friend point operator-(point a, point b) {return a -= b;}
    point& operator*=(T z) {x *= z; y *= z; return *this;}
    point& operator/=(T z) {x /= z; y /= z; return *this;}
    friend point operator*(point a, T z) {return a *= z;}
    friend point operator/(point a, T z) {return a /= z;}
    friend T abs(point const& a) {return sqrt(a.x * a.x + a.y * a.y);}
    friend istream &operator>>(istream &input, point &a) {return input >> a.x >> a.y;}
    friend ostream &operator<<(ostream &output, const point &a) {return output << '[' << a.x << ", " << a.y << ']';}
};
namespace nt {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    int64_t rand(int64_t l, int64_t r) {
        return l + rng() % (r - l + 1);
    }

    template <typename T = int64_t, typename U = __int128_t>
    T pow(T a, T b, T mod) {
        a %= mod;
        T r = 1;

        for(T i = b; i; i >>= 1, a = (U)a * a % mod) if(i & 1) {
            r = (U)r * a % mod;
        }

        return r;
    }

    template <typename T>
    T gcd(T a, T b, T &x, T &y) {
        if(!b) {
            x = 1, y = 0;
            return a;
        }

        T x1, y1;
        T g = gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);

        return g;
    }

    int64_t inverse(int64_t a, int64_t m) {
        int64_t x, y;
        int64_t g = gcd(a, m, x, y);
        if(g > 1) 
            return -1;
        x = (x % m + m) % m;
        return x;
    }

    // Returns minimum x for which a ^ x % m = b % m, a and m are coprime.
    int solve(int a, int b, int m) {
        a %= m, b %= m;
        int n = sqrt(m) + 1;

        int an = 1;
        for (int i = 0; i < n; ++i)
            an = (an * 1LL * a) % m;

        unordered_map<int, int> vals;
        for (int q = 0, cur = b; q <= n; ++q) {
            vals[cur] = q;
            cur = (cur * 1LL * a) % m;
        }

        for (int p = 1, cur = 1; p <= n; ++p) {
            cur = (cur * 1LL * an) % m;
            if (vals.count(cur)) {
                int ans = n * p - vals[cur];
                return ans;
            }
        }
        return -1;
    }
    
    // returns primes upto n 
    vector <int> sieve(int n) {
        vector <int> prime, mn(n + 1, 0);
        for(int i = 2; i <= n; i++) {
            if(!mn[i]) {
                prime.push_back(i);
            }
            for(int j = 0; j < prime.size() && i * prime[j] <= n; j++) {
                mn[i * prime[j]] = prime[j];
                if(i % prime[j] == 0) {
                    break;
                }
            }
        }

        return prime;
    }

    namespace MillerRabin{

        bool isComposite(int64_t x, int64_t a, int64_t d, int64_t s) {
            int64_t y = pow(a, d, x);
            if(y == 1 || y == x - 1) return false;

            for(int64_t r = 1; r < s; r++) {
                y = (__int128_t)y * y % x;
                if(y == x - 1) return false;
            }

            return true;
        }

        bool isPrime(int64_t x) {
            if(x < 2) return false;
            for(int64_t a: sieve(40)) if(a == x) {
                return true;
            }
            int64_t r = 0, d = x - 1;
            
            while(d % 2 == 0) {
                d /= 2;
                ++r;
            }
            for(int64_t a: sieve(40)) if(isComposite(x, a, d, r)) {
                    return false;
            }
            return true;
        }
    }

    namespace Rho{

        int64_t f(int64_t x, int64_t c, int64_t mod) {
            return ((__int128_t)x * x + c) % mod; 
        }

        int64_t brent(int64_t n) {
            int64_t x = rand(2, n), g = 1, q = 1, xs, y, c = rand(1, n);

            int m = 128;
            int l = 1;
            while (g == 1) {
                y = x;
                for (int i = 1; i < l; i++)
                    x = f(x, c, n);
                int k = 0;
                while (k < l && g == 1) {
                    xs = x;
                    for (int i = 0; i < m && i < l - k; i++) {
                        x = f(x, c, n);
                        q = (__int128_t)q * abs(y - x) % n;
                    }
                    g = __gcd(q, n);
                    k += m;
                }
                l *= 2;
            }
            if (g == n) {
                do {
                    xs = f(xs, c, n);
                    g = __gcd(abs(xs - y), n);
                } while (g == 1);
            }
            return g;
        }
        vector <int64_t> factor(int64_t n) {
            if(n == 1)
                return {};
            if(MillerRabin::isPrime(n)) {
                return {n};
            }
            int64_t dx = n;
            while(dx == n) {
                dx = brent(n);
            }
            auto L = factor(dx), R = factor(n / dx);
            L.insert(L.end(), R.begin(), R.end());

            return L;
        }
    }
}

using namespace nt;

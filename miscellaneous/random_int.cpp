mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int64_t rnd(int64_t l, int64_t r) {
    return l + rng() % (r - l + 1);
}
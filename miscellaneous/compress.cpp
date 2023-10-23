template <typename T>
vector <T> compress(vector <T> a) {
    auto b = a;
    sort(b.begin(), b.end());
    for(auto &x: a) 
        x = upper_bound(b.begin(), b.end(), x) - b.begin();
    return a;
}
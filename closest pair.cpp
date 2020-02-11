vector <pair <int, int> > v ;

int dist(pair <int, int> &a, pair <int, int> &b) {
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

int res = 1e18;

int f(int l, int r)  {
    if(r - l <= 3) {
        for(int i = l; i <= r; i++)
            for(int j = l; j < i; j++)
                res = min(res, dist(v[i], v[j]));
        return res;
    }
    int mid = (l + r) >> 1;
    int x = f(l, mid);
    int y = f(mid, r);
    res = min(x, y);
    vector <pair<int, int>> a;
    for(int i = l; i <= r; i++) if(abs(v[i].first - v[mid].first) < res) a.push_back(v[i]);
    sort(a.begin(), a.end(), [](pair <int, int> p, pair <int, int> q) {
        return p.second < q.second;
    });
    int z = ceil(sqrt(res));
    for(int i = 0; i < a.size(); i++)
        for(int j = i - 1; j >= 0 && a[i].second - a[j].second < z; j--)
            res = min(res, dist(a[i], a[j]));
    return res;
}

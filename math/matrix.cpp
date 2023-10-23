int mod;
 
struct matrix{
	vector <vector <int> > x;
	matrix(vector<vector <int> > m) : x(m) {}
	matrix operator *(matrix a) {
		int p = x.size(), q = x[0].size(), r = a.x[0].size();
		vector <vector <int> > y = a.x, z(p, vector <int> (r, 0));
		for(int i = 0; i < p; i++) {
			for(int j = 0; j < q; j++) {
				for(int k = 0; k < r; k++) {
					z[i][j] += 1LL * x[i][k] * y[k][j] % mod;
					z[i][j] %= mod;
				}
			}
		}
		return matrix(z);
	}
	matrix operator ^(int n) {
		matrix r(vector <vector<int> > (x.size(), vector <int> (x.size(), 0))), a = *this;
		for(int i = 0; i < x.size(); i++) r.x[i][i] = 1;
		for(int i = n; i > 0; i >>= 1, a = a * a) if(i & 1) {
			r = r * a;
		}
		return r;
	}
};

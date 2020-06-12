int mod = 1e9 + 7;
 
struct Matrix {
    int n, m;
    vector < vector <int> > mat;
    Matrix(vector < vector <int> > M) : mat(M), n(M.size()), m(M[0].size()) {}
    static Matrix id(int n) {
        vector < vector <int> > I(n, vector <int> (n, 0));
            for(int i = 0; i < n; i++) {
                I[i][i] = 1;
            }
        return Matrix(I);
    }
    Matrix operator * (Matrix A) {
        int N = n, M = A.m, O = m;
        vector < vector <int> > Temp(N, vector <int> (M, 0));
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                for(int k = 0; k < O; k++) {
                    Temp[i][j] = (Temp[i][j] + mat[i][k] * A.mat[k][j]) % mod;
                }
            }
        }
        return Matrix(Temp);
    }
    friend ostream& operator << (ostream &out, Matrix A) ;
};
 
ostream& operator << (ostream &out, Matrix A) {
    for(int i = 0; i < A.n; i++, cout << endl) {
        for(int j = 0; j < A.m; j++) {
            cout << A.mat[i][j] << " ";
        }
    }
}
 
 
Matrix POW(int n, Matrix M, int l) {
    Matrix ret = M.id(l);
    while(n) {
        if(n & 1) {
            ret = ret * M;
        }
        n /= 2;
        M = M * M;
    }
    return ret;
}

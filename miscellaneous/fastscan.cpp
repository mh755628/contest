template <class T> inline void fastScan(T &x){
    register char c = getchar();
    int neg = 0; x = 0;
    for(; (c < 48 || c > 57) && (c != '-'); c = getchar());
    if(c == '-') { neg = 1; c = getchar(); }
    for(; c > 47 && c < 58; c = getchar())
        x = (x << 1) + (x << 3) + c - 48;
    if(neg) x = -x;
}
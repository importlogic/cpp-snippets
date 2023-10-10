int expo(int a, int n, int mod){ 
    int res = 1;

    while(n){ 
        if(n & 1) {
            res = (res * a) % mod;
            --n;
        } 
        else {
            a = (a * a) % mod;
            n >>= 1;
        }
    } 

    return res;
}
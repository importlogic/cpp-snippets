const int mod = 1e9 + 7;
const int MAX = 1e6 + 10;
int fact[MAX], inv_fact[MAX];

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

int ncr(int n, int r){
	if(r > n)
		return 0;

	int ans = (inv_fact[r] * inv_fact[n - r]) % mod;
	ans = (ans * fact[n]) % mod;

	return ans;
}

void pre_ncr(){
    fact[0] = fact[1] = 1;
    for(int i = 2; i < MAX + 1; i++)
        fact[i] = (fact[i - 1] * i) % mod;

    inv_fact[MAX - 1] = expo(fact[MAX - 1], mod - 2, mod);

    for(int i = MAX - 2; i > -1; i--)
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;
}
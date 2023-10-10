vector<bool> sieve(int n){
    vector<bool> prime(n + 1, 1); 
    prime[0] = prime[1] = 0; 

    for(int i = 2; i * i <= n; i++){
        if(prime[i]){
            for(int j = i * i; j <= n; j += i) 
                prime[j] = 0;
        }
    } 

    return prime;
}
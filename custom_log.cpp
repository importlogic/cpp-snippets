int clog(int x, int y){
    int res = 0;
    __int128 val = 1;
    
    do {
        __int128 next = val * y;
        
        if(next <= x){
            ++res;
            val = next;
        }
        else
            break;

    } while(1);
    
    return res;
}
/*
    1. The seg_tree is based on an [ input ] vector assuming 0 based indexing.
    2. Set the value of N as 4 * n where n is the maximum input vector size.
    3. Everything has been done you just need to call build, update and query functions.
    4. The code is for range sum, make your changes accordingly.
*/

const int N = 8e5;
vector<int> seg_tree(N);
vector<int> lazy_tree(N);

void build(int node, int low, int high, vector<int> &input){
    if(low == high){
        seg_tree[node] = input[low];
        lazy_tree[node] = 0;
        return;
    }

    int mid = low + (high - low) / 2;
    build(2 * node + 1, low, mid, input);
    build(2 * node + 2, mid + 1, high, input);

    seg_tree[node] = seg_tree[2 * node + 1] + seg_tree[2 * node + 2];
}

void update(int node, int low, int high, int rangelow, int rangehigh, int dx){
    if(lazy_tree[node]){
        int size = high - low + 1;

        seg_tree[node] += size * lazy_tree[node];

        if(low != high){
            lazy_tree[2 * node + 1] += lazy_tree[node];
            lazy_tree[2 * node + 2] += lazy_tree[node];
        }

        lazy_tree[node] = 0;
    }

    if(low > rangehigh or high < rangelow)
        return;

    if(low >= rangelow and high <= rangehigh){
        int size = high - low + 1;

        seg_tree[node] += size * dx;

        if(low != high){
            lazy_tree[2 * node + 1] += dx;
            lazy_tree[2 * node + 2] += dx;
        }

        return;
    }

    int mid = low + (high - low) / 2;

    update(2 * node + 1, low, mid, rangelow, rangehigh, dx);
    update(2 * node + 2, mid + 1, high, rangelow, rangehigh, dx);

    seg_tree[node] = seg_tree[2 * node + 1] + seg_tree[2 * node + 2];
}

int query(int node, int low, int high, int rangelow, int rangehigh) {
    if(lazy_tree[node]){
        int size = high - low + 1;

        seg_tree[node] += size * lazy_tree[node];

        if(low != high){
            lazy_tree[2 * node + 1] += lazy_tree[node];
            lazy_tree[2 * node + 2] += lazy_tree[node];
        }

        lazy_tree[node] = 0;
    }

    if(low > rangehigh or high < rangelow)
        return 0;

    if(low >= rangelow and high <= rangehigh)
        return seg_tree[node];

    int mid = low + (high - low) / 2;

    int x = query(2 * node + 1, low, mid, rangelow, rangehigh);
    int y = query(2 * node + 2, mid + 1, high, rangelow, rangehigh);

    return x + y;
}
/*
    1. The tree is based on an [ input ] vector assuming 1 based indexing.
    2. Everything has been done you just need to call update and query functions.
    3. The code is for range sum, make your changes accordingly.
*/

vector<int> tree(4 * n);
vector<int> lazy(4 * n);

function<void(int, int, int)> build = [&](int node, int low, int high){
	if(low == high){
		tree[node] = input[low];
		lazy[node] = 0;
		return;
	}

	int mid = low + (high - low) / 2;
	build(2 * node, low, mid);
	build(2 * node + 1, mid + 1, high);

	tree[node] = tree[2 * node] + tree[2 * node + 1];
};

function<void(int, int, int, int, int, int)> update = [&](int node, int low, int high, int rangelow, int rangehigh, int dx){
	if(lazy[node]){
		int size = high - low + 1;

		tree[node] += size * lazy[node];

        if(low != high){
    		lazy[2 * node] += lazy[node];
    		lazy[2 * node + 1] += lazy[node];
        }

		lazy[node] = 0;
	}

    if(low > rangehigh or high < rangelow)
        return;

    if(low >= rangelow and high <= rangehigh){
        int size = high - low + 1;

        tree[node] += size * dx;

        if(low != high){
            lazy[2 * node] += dx;
            lazy[2 * node + 1] += dx;
        }

        return;
    }

    int mid = low + (high - low) / 2;

    update(2 * node, low, mid, rangelow, rangehigh, dx);
    update(2 * node + 1, mid + 1, high, rangelow, rangehigh, dx);
};

function<int(int, int, int, int, int)> query = [&](int node, int low, int high, int rangelow, int rangehigh) -> int {
    if(lazy[node]){
        int size = high - low + 1;

        tree[node] += size * lazy[node];

        if(low != high){
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }

        lazy[node] = 0;
    }

    if(low > rangehigh or high < rangelow)
        return 0;

    if(low >= rangelow and high <= rangehigh)
        return tree[node];

    int mid = low + (high - low) / 2;

    int x = query(2 * node, low, mid, rangelow, rangehigh);
    int y = query(2 * node + 1, mid + 1, high, rangelow, rangehigh);

    return x + y;
};

build(1, 1, n);
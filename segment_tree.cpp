/*
    1. The seg_tree is based on an [ input ] vector assuming 1 based indexing.
    2. Everything has been done you just need to call update and query functions.
    3. The code is for range sum, make your changes accordingly.
*/

vector<int> seg_tree(4 * n);
vector<int> lazy_tree(4 * n);

function<void(int, int, int)> build = [&](int node, int low, int high){
	if(low == high){
		seg_tree[node] = input[low];
		lazy_tree[node] = 0;
		return;
	}

	int mid = low + (high - low) / 2;
	build(2 * node, low, mid);
	build(2 * node + 1, mid + 1, high);

	seg_tree[node] = seg_tree[2 * node] + seg_tree[2 * node + 1];
};

function<void(int, int, int, int, int, int)> update = [&](int node, int low, int high, int rangelow, int rangehigh, int dx){
	if(lazy_tree[node]){
		int size = high - low + 1;

		seg_tree[node] += size * lazy_tree[node];

        if(low != high){
    		lazy_tree[2 * node] += lazy_tree[node];
    		lazy_tree[2 * node + 1] += lazy_tree[node];
        }

		lazy_tree[node] = 0;
	}

    if(low > rangehigh or high < rangelow)
        return;

    if(low >= rangelow and high <= rangehigh){
        int size = high - low + 1;

        seg_tree[node] += size * dx;

        if(low != high){
            lazy_tree[2 * node] += dx;
            lazy_tree[2 * node + 1] += dx;
        }

        return;
    }

    int mid = low + (high - low) / 2;

    update(2 * node, low, mid, rangelow, rangehigh, dx);
    update(2 * node + 1, mid + 1, high, rangelow, rangehigh, dx);

    seg_tree[node] = seg_tree[2 * node] + seg_tree[2 * node + 1];
};

function<int(int, int, int, int, int)> query = [&](int node, int low, int high, int rangelow, int rangehigh) -> int {
    if(lazy_tree[node]){
        int size = high - low + 1;

        seg_tree[node] += size * lazy_tree[node];

        if(low != high){
            lazy_tree[2 * node] += lazy_tree[node];
            lazy_tree[2 * node + 1] += lazy_tree[node];
        }

        lazy_tree[node] = 0;
    }

    if(low > rangehigh or high < rangelow)
        return 0;

    if(low >= rangelow and high <= rangehigh)
        return seg_tree[node];

    int mid = low + (high - low) / 2;

    int x = query(2 * node, low, mid, rangelow, rangehigh);
    int y = query(2 * node + 1, mid + 1, high, rangelow, rangehigh);

    return x + y;
};

build(1, 1, n);
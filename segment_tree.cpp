class seg_tree {
  int N;
  vector<int> seg, lazy;
  vector<int> input;

  void _build_sum(int node, int low, int high) {
    if(low == high){
      seg[node] = input[low];
      lazy[node] = 0;
      return;
    }

    int mid = low + (high - low) / 2;
    _build_sum(2 * node + 1, low, mid);
    _build_sum(2 * node + 2, mid + 1, high);

    seg[node] = seg[2 * node + 1] + seg[2 * node + 2];      
  }

  void _update_sum(int node, int low, int high, int rangelow, int rangehigh, int dx){
    if(lazy[node]){
      int size = high - low + 1;

      seg[node] += size * lazy[node];

      if(low != high){
          lazy[2 * node + 1] += lazy[node];
          lazy[2 * node + 2] += lazy[node];
      }

      lazy[node] = 0;
    }

    if(low > rangehigh or high < rangelow)
        return;

    if(low >= rangelow and high <= rangehigh){
      int size = high - low + 1;

      seg[node] += size * dx;

      if(low != high){
          lazy[2 * node + 1] += dx;
          lazy[2 * node + 2] += dx;
      }

      return;
    }

    int mid = low + (high - low) / 2;

    _update_sum(2 * node + 1, low, mid, rangelow, rangehigh, dx);
    _update_sum(2 * node + 2, mid + 1, high, rangelow, rangehigh, dx);

    seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
  }

  int _query_sum(int node, int low, int high, int rangelow, int rangehigh) {
    if(lazy[node]){
      int size = high - low + 1;

      seg[node] += size * lazy[node];

      if(low != high){
          lazy[2 * node + 1] += lazy[node];
          lazy[2 * node + 2] += lazy[node];
      }

      lazy[node] = 0;
    }

    if(low > rangehigh or high < rangelow)
        return 0;

    if(low >= rangelow and high <= rangehigh)
        return seg[node];

    int mid = low + (high - low) / 2;

    int x = _query_sum(2 * node + 1, low, mid, rangelow, rangehigh);
    int y = _query_sum(2 * node + 2, mid + 1, high, rangelow, rangehigh);

    return x + y;
  }

public:
  seg_tree(int n, vector<int> &v) {
    N = n;
    input = v;
    seg.resize(4 * N, 0);
    lazy.resize(4 * N, 0);
  }

  void build_sum() { _build_sum(0, 0, N - 1); }
  void update_sum(int l, int r, int dx) { _update_sum(0, 0, N - 1, l, r, dx); }
  int query_sum(int l, int r) { return _query_sum(0, 0, N - 1, l, r); }
};

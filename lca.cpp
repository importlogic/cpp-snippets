/*
    1. This code assumes a 0 based tree [ g ] with n vertices.
    2. Set the value of N as the maximum number of vertices in the tree.
    3. Everything has been done you just need to call settingParents and get_lca function.
*/

const int N = 1e5;
const int LOG = log2(N) + 1;
vector<vector<int>> up(N, vector<int>(LOG, -1));
vector<int> depth(N);

void settingParents(int node, int parent, int d, vector<vector<int>> &g) {
    up[node][0] = parent;
    depth[node] = d;

    for(int i = 1; i < LOG; i++){
        if(up[node][i - 1] != -1)
            up[node][i] = up[up[node][i - 1]][i - 1];
    }

    for(auto child : g[node]){
        if(child != parent)
            settingParents(child, node, d + 1, g);
    }
}

int get_lca(int x, int y) {
    if(depth[x] < depth[y])
        swap(x, y);

    int dx = depth[x] - depth[y];

    for(int i = LOG - 1; i > -1; i--){
        if((dx >> i) & 1)
            x = up[x][i];
    }

    if(x == y)
        return x;

    for(int i = LOG - 1; i > -1; i--){
        if(up[x][i] != up[y][i]){
            x = up[x][i];
            y = up[y][i];
        }
    }

    return up[x][0];
}